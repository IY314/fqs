#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <argparse/argparse.hpp>

#include "fqs.hh"
#include "lex.hh"

void parseArgs(argparse::ArgumentParser &args, int argc,
               const char *const *argv) {
    args.add_argument("--output", "-o");
    args.add_argument("--repl", "-r").default_value(false).implicit_value(true);
    args.add_argument("files").remaining();
    try {
        args.parse_args(argc, argv);
    } catch (std::runtime_error e) {
        std::cerr << e.what() << '\n' << args;
        std::exit(1);
    }
}

fqs::RunResult run(const std::string &fn, const std::string &text) {
    fqs::lex::Lexer lexer(fn, text);
    auto lexerResult = lexer.makeTokens();
    if (const auto *error = std::get_if<fqs::err::FQSError>(&lexerResult)) {
        return *error;
    }
    return std::get<std::vector<fqs::token::Token>>(lexerResult);
}

void printRun(const std::string &fn, const std::string &text) {
    auto result = run(fn, text);
    if (const auto *error = std::get_if<fqs::err::FQSError>(&result)) {
        std::cerr << error->str();
    } else if (const auto *res =
                   std::get_if<std::vector<fqs::token::Token>>(&result)) {
        std::cout << '[';
        for (const auto &tok : *res) {
            std::cout << tok.str() << ", ";
        }
        std::cout << "]\n";
    }
}

std::string readFile(const std::string &fn) {
    std::ifstream is(fn);
    std::ostringstream result;
    std::string line;
    while (std::getline(is, line)) {
        result << line << '\n';
    }
    return result.str();
}

int main(int argc, const char *const *argv) {
    argparse::ArgumentParser args("fqs", FQS_VERSION);
    parseArgs(args, argc, argv);
    std::vector<std::string> files;
    if (args.get<bool>("--repl")) {
        while (true) {
            std::string text;
            std::cout << '>';
            std::getline(std::cin, text);
            printRun("<stdin>", text);
        }
    } else if ((files = args.get<std::vector<std::string>>("files")).size()) {
        for (const std::string &file : files) {
            const std::string text = readFile(file);
            printRun(file, text);
        }
    }
}
