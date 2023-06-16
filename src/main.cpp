#include "../include/ansi_wrapper.hpp"
#include "../include/config.hpp"
#include "../include/config_json_reader.hpp"
#include "../include/config_option_reader.hpp"
#include "../include/event_dispatch.hpp"
#include "../include/file_item_reader.hpp"
#include "../include/history_manager.hpp"
#include "../include/item_cache.hpp"
#include "../include/item_exact_matcher.hpp"
#include "../include/item_fuzzy_matcher.hpp"
#include "../include/item_list.hpp"
#include "../include/item_matcher.hpp"
#include "../include/item_regex_matcher.hpp"
#include "../include/item_sorter.hpp"
#include "../include/jfind_strategy.hpp"
#include "../include/logger.hpp"
#include "../include/process_item_reader.hpp"
#include "../include/style_manager.hpp"
#include "../include/user_interface.hpp"
#include "../include/utf8_line_editor.hpp"
#include "../include/util.hpp"
#include <climits>
#include <csignal>
#include <cstring>
#include <thread>

extern "C" {
#include <fcntl.h>
}

static Config &config = Config::instance();
static AnsiWrapper &ansi = AnsiWrapper::instance();
static EventDispatch &eventDispatch = EventDispatch::instance();
static Logger logger = Logger("main");

static InputReader inputReader;
static StyleManager styleManager(stderr);
static HistoryManager *historyManager = nullptr;
static ItemCache itemCache;
static ItemList itemList(stderr, &styleManager, &itemCache);
static Utf8LineEditor editor(stderr);
static UserInterface userInterface(stderr, &styleManager, &itemList, &editor);

void printResult(Key key, Item *selected, const char *input) {
    if (config.showKey && (selected || config.acceptNonMatch)) {
        printf("%d\n", key);
    }
    if (selected) {
        if (!config.selectHint || config.selectBoth) {
            printf("%s\n", selected->text);
        }
        if (config.selectHint || config.selectBoth) {
            printf("%s\n", selected->text + strlen(selected->text) + 1);
        }
    }
    else if (config.acceptNonMatch) {
        printf("%s\n", input);
    }
}

void emitResizeEvent() {
    winsize ws;
    if (ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1) {
        ansi.restoreTerm();
        fprintf(stderr, "failed to query terminal size\n");
        exit(1);
    }
    eventDispatch.dispatch(std::make_shared<ResizeEvent>(ws.ws_col, ws.ws_row));
}

void finish() {
    Item *selected = userInterface.getSelected();
    if (selected && historyManager) {
        historyManager->writeHistory(selected);
        delete historyManager;
    }
    ansi.restoreTerm();
    printResult(
        userInterface.getSelectedKey(), selected, editor.getText().c_str()
    );
    logger.log("done");
    Logger::close();
    exit(0);
}

void signalHandler(int sig) {
    switch (sig) {
        case SIGTERM:
            finish();
            break;
        case SIGINT:
            eventDispatch.dispatch(std::make_shared<KeyEvent>(K_CTRL_C));
            break;
        case SIGWINCH:
            logger.log("received SIGWINCH");
            emitResizeEvent();
            break;
        default:
            logger.log("received unknown signal %d", sig);
            break;
    }
}

int main(int argc, const char **argv) {
    if (!readConfig(&styleManager, argc, argv)) {
        return 1;
    }

    if (config.logFile.size()) {
        Logger::open(config.logFile.c_str());
    }

    if ((!config.command.size() && isatty(STDIN_FILENO)) || config.showHelp) {
        displayHelp(argv[0]);
        return 0;
    }

    createStyles(&styleManager);

    if (!config.historyFile.empty()) {
        historyManager = new HistoryManager(config.historyFile);
        historyManager->setHistoryLimit(config.historyLimit);
        historyManager->readHistory();
    }

    editor.input(config.query);

    int fd = open("/dev/tty", O_RDONLY);
    ansi.setInputFileNo(fd);
    inputReader.setFileDescriptor(fd);

    // enable unicode
    setlocale(LC_ALL, "en_US.UTF-8");

    ansi.setOutputFile(stderr);

    signal(SIGWINCH, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    ansi.initTerm();
    ansi.enableMouse();
    ansi.setCursor(true);
    emitResizeEvent();

    JfindStrategy *jfindStrategy = config.command.size()
        ? (JfindStrategy *)new InteractiveCommandStrategy(itemCache)
        : (JfindStrategy *)new FuzzyFindStrategy(itemCache);

    userInterface.setThreadsafeReading(jfindStrategy->isThreadsafeReading());
    jfindStrategy->start();
    new std::thread(&InputReader::start, &inputReader);
    userInterface.start();

    logger.log("edited unexpectedly");
    ansi.restoreTerm();
    return 1;
}
