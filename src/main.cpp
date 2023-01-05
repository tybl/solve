#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

enum TokenType {
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACE,
	RIGHT_BRACE,
	COMMA,
	DOT,
	MINUS,
	PLUS,
	SEMICOLON,
	SLASH,
	STAR,

	BANG,
	BANG_EQUAL,
	EQUAL,
	EQUAL_EQUAL,
	GREATER,
	GREATER_EQUAL,
	LESS,
	LESS_EQUAL,

	IDENTIFIER,
	STRING,
	NUMBER,

	AND,
	CLASS,
	ELSE,
	FALSE,
	FUN,
	FOR,
	IF,
	NIL,
	OR,
	PRINT,
	RETURN,
	SUPER,
	THIS,
	TRUE,
	VAR,
	WHILE,
	END_OF_FILE
};

class Object {

};

class Token {
  TokenType type;
  std::string lexeme;
  Object literal;
  int line;
public:
  Token(TokenType type, std::string lexeme, Object literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}
  [[nodiscard]] auto to_string() const -> std::string {
    return lexeme;
  }
};

class Scanner {
  std::string m_source;
  std::vector<Token> tokens;
  int start = 0;
  int current = 0;
  int line = 1;
public:
  explicit Scanner(std::string  source)
    : m_source(std::move(source)) {}

  std::vector<Token> scan_tokens() {
    while (!is_at_end()) {
      start = current;
      scan_token();
    }
    tokens.emplace_back(END_OF_FILE, "", Object(), line);
    return tokens;
  }
private:
  void add_token(TokenType type) {
    add_token(type, Object());
  }

  void add_token(TokenType type, Object literal) {
    std::string text = m_source.substr(start, current);
    tokens.emplace_back(type, text, literal, line);
  }

  char advance() {
    return m_source.at(current++);
  }

  [[nodiscard]] bool is_at_end() const {
    return m_source.length() <= current;
  }

  void scan_token() {
    char c = advance();
    switch (c) {
      case '(': add_token(LEFT_PAREN); break;
      case ')': add_token(RIGHT_PAREN); break;
      case '{': add_token(LEFT_BRACE); break;
      case '}': add_token(RIGHT_BRACE); break;
      case ',': add_token(COMMA); break;
      case '.': add_token(DOT); break;
      case '-': add_token(MINUS); break;
      case '+': add_token(PLUS); break;
      case ';': add_token(SEMICOLON); break;
      case '*': add_token(STAR); break;
      default: break;
    }
  }
};

class Solve {
  bool m_had_error = false;
public:
  void error(int line, std::string const& message) {
    report(line, "", message);
  }
  void report(int line, std::string const& where, std::string const& message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    m_had_error = true;
  }

  void run(std::string const& input) {
    Scanner scanner(input);
    auto tokens = scanner.scan_tokens();
    for (auto const& token : tokens) {
      std::cout << token.to_string() << std::endl;
    }
  }

  void run_file(std::string const& path) {
    std::ifstream file(path);
    std::string input(std::istreambuf_iterator<char>{file}, {});
    run(input);
    if (m_had_error) exit(65);
  }

  void run_prompt() {
    std::string input;
    while (true) {
      std::cout << "> ";
      std::getline(std::cin, input);
      if (input.empty()) break;
      run(input);
      m_had_error = false;
    }
  }

};

int main(int argc, char* argv[]) {
  Solve solver;
  if (2 < argc) {
    return -1;
  } else if (2 == argc) {
    solver.run_file(argv[1]);
  } else if (1 == argc) {
    solver.run_prompt();
  }
  return 0;
}
