#include "../include/util.hpp"

#include <vector>

namespace fs = std::filesystem;

std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> words;
    std::string word = "";

    for (char c : str) {
        if (c == delim) {
            words.push_back(word);
            word = "";
        }
        else {
            word += c;
        }
    }
    if (word.size() > 0) {
        words.push_back(word);
    }
    return words;
}

std::string toLower(std::string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

fs::path expandUserPath(std::string userPath) {
    if (userPath == "~") {
        return getenv("HOME");
    }
    if (userPath.starts_with("~/")) {
        return getenv("HOME") / fs::path(userPath.substr(2));
    }
    return userPath;
}

int mod(int n, int m) {
    return ((n % m) + m) % m;
}

bool isVowel(char c) {
    switch (tolower(c)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

bool isInteger(const char *str) {
    if (!str || !*str) {
        return false;
    }
    if (*str == '-') {
        str++;
    }
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

void replace(std::string &str, char from, char to) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == from) {
            str[i] = to;
        }
    }
}

void displayHelp(const char *name) {
    printf("usage: %s [options]\n", name);
    printf("\n");
    printf("OPTIONS:\n");
    printf("    --help                        Display this dialog\n");
    printf("    --hints                       Read hints from stdin (every "
           "second line)\n");
    printf("    --select-hint                 Print the hint to stdout\n");
    printf("    --select-both                 Print both the item and hint to "
           "stdout\n");
    printf("    --accept-non-match            Accept the user's query if "
           "nothing matches\n");
    printf("    --matcher=MATCHER             Override matching algorithm to "
           "MATCHER (fuzzy or regex)\n");
    printf("    --case-mode=SENSITIVITY       Override case sensitivity to "
           "SENSITIVITY (sensitive, insensitive, or smart)\n");
    printf("    --history=FILE                Read and write match history to "
           "FILE\n");
    printf("    --history-limit=INT           Number of items to store in the "
           "history file\n");
    printf("    --prompt=PROMPT               Set the query prompt to PROMPT\n"
    );
    printf("    --query=QUERY                 Set the starting query to QUERY\n"
    );
    printf("    --command                     Use COMMAND to filter items. See "
           "the COMMAND section for details\n");
    printf("    --additional-keys=KEY_LIST    Accept the item at the cursor if "
           "a key in KEY_LIST is pressed.\n");
    printf("                                  KEY_LIST is provided as a comma "
           "separated list of ascii codes.\n");
    printf("    --show-key                    Print the keycode which was used "
           "to select an item.\n");
    printf("                                  Unless provided in "
           "--additional-keys, mouse and enter will both return 0\n");
    printf("\n");
    printf("CONFIG (~/.config/jfind/config.json):\n");
    printf(
        "    selector: STRING              The selector of an unselected item\n"
    );
    printf(
        "    active_selector: STRING       The selector of the selected item\n"
    );
    printf("    prompt: STRING                The default prompt\n");
    printf("    prompt_gap: INT               The distance between the prompt "
           "and query\n");
    printf("    history_limit: INT            Default number of items to store "
           "in the history file\n");
    printf("    min_hint_spacing: INT         Minimum gap between an item and "
           "its hint\n");
    printf("    min_hint_width: INT           Minimum width a hint should be "
           "before it is shown\n");
    printf(
        "    max_hint_width: INT           Maximum width a hint can grow to\n"
    );
    printf("    show_spinner: BOOL            Show a spinner animation at the "
           "bottom right when loading\n");
    printf("    style: STYLE OBJECT           Custom styles. See STYLES for "
           "keys, and STYLE OBJECT for values\n");
    printf("    matcher: MATCHER              Default matching algorithm "
           "(fuzzy or regex)\n");
    printf("    case_mode: SENSITIVITY        Default case sensitivity "
           "(sensitive, insensitive, or smart)\n");
    printf("\n");
    printf("STYLES:\n");
    printf("    item                          An unselected item\n");
    printf("    active_item                   A selected item\n");
    printf("    hint                          The hint of an unselected item\n"
    );
    printf("    active_hint                   The hint of a selected item\n");
    printf(
        "    selector                      The selector of an unselected item\n"
    );
    printf("    active_selector               The selector of a selected item\n"
    );
    printf("    active_row                    The gap between a selected item "
           "and its hint\n");
    printf("    row                           The gap between an unselected "
           "item and its hint\n");
    printf("    search_prompt                 The query prompt\n");
    printf("    search                        The query that the user enters\n"
    );
    printf(
        "    search_row                    Everywhere else on the search row\n"
    );
    printf("    background                    Everywhere else on the screen\n");
    printf("\n");
    printf("STYLE OBJECT:\n");
    printf("    fg: STRING                    Foreground color as one of COLOR "
           "NAMES or a hex string\n");
    printf("    bg: STRING                    Background color as one of COLOR "
           "NAMES or a hex string\n");
    printf("    attr: LIST                    A list of ATTRIBUTES\n");
    printf("\n");
    printf("COLOR NAMES:\n");
    printf("    red, green, blue, cyan, yellow, magenta, black, white\n");
    printf("    A color name may be prefixed with 'bright_' to use the bright "
           "variant\n");
    printf("\n");
    printf("ATTRIBUTES:\n");
    printf("    bold, italic, blink, reverse,\n");
    printf("    underline, curly_underline, double_underline, "
           "dotted_underline, dashed_underline\n");
    printf("\n");
    printf("COMMAND:\n");
    printf("    You can use the --command flag to run spawn a process whenever "
           "the query changes.\n");
    printf(
        "    The stdout of this process will be displayed as items in jfind.\n"
    );
    printf("    For an interactive example, run 'jfind --command=\"seq {}\"'.\n"
    );
    printf("\n");
    printf("Input should be piped into jfind for it to be useful. You can try "
           "the following example:\n");
    printf("    seq 100 | %s\n", name);
}
