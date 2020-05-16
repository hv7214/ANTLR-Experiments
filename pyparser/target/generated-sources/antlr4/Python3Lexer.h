
    #include<bits/stdc++.h>
    #include "Python3Parser.h"
    using namespace std;
    using namespace antlr4;


// Generated from Python3.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  Python3Lexer : public antlr4::Lexer {
public:
  enum {
    STRING = 1, NUMBER = 2, INTEGER = 3, DEF = 4, RETURN = 5, RAISE = 6, 
    FROM = 7, IMPORT = 8, AS = 9, GLOBAL = 10, NONLOCAL = 11, ASSERT = 12, 
    IF = 13, ELIF = 14, ELSE = 15, WHILE = 16, FOR = 17, IN = 18, TRY = 19, 
    FINALLY = 20, WITH = 21, EXCEPT = 22, LAMBDA = 23, OR = 24, AND = 25, 
    NOT = 26, IS = 27, NONE = 28, TRUE = 29, FALSE = 30, CLASS = 31, YIELD = 32, 
    DEL = 33, PASS = 34, CONTINUE = 35, BREAK = 36, ASYNC = 37, AWAIT = 38, 
    NEWLINE = 39, NAME = 40, STRING_LITERAL = 41, BYTES_LITERAL = 42, DECIMAL_INTEGER = 43, 
    OCT_INTEGER = 44, HEX_INTEGER = 45, BIN_INTEGER = 46, FLOAT_NUMBER = 47, 
    IMAG_NUMBER = 48, DOT = 49, ELLIPSIS = 50, STAR = 51, OPEN_PAREN = 52, 
    CLOSE_PAREN = 53, COMMA = 54, COLON = 55, SEMI_COLON = 56, POWER = 57, 
    ASSIGN = 58, OPEN_BRACK = 59, CLOSE_BRACK = 60, OR_OP = 61, XOR = 62, 
    AND_OP = 63, LEFT_SHIFT = 64, RIGHT_SHIFT = 65, ADD = 66, MINUS = 67, 
    DIV = 68, MOD = 69, IDIV = 70, NOT_OP = 71, OPEN_BRACE = 72, CLOSE_BRACE = 73, 
    LESS_THAN = 74, GREATER_THAN = 75, EQUALS = 76, GT_EQ = 77, LT_EQ = 78, 
    NOT_EQ_1 = 79, NOT_EQ_2 = 80, AT = 81, ARROW = 82, ADD_ASSIGN = 83, 
    SUB_ASSIGN = 84, MULT_ASSIGN = 85, AT_ASSIGN = 86, DIV_ASSIGN = 87, 
    MOD_ASSIGN = 88, AND_ASSIGN = 89, OR_ASSIGN = 90, XOR_ASSIGN = 91, LEFT_SHIFT_ASSIGN = 92, 
    RIGHT_SHIFT_ASSIGN = 93, POWER_ASSIGN = 94, IDIV_ASSIGN = 95, SKIP_ = 96, 
    UNKNOWN_CHAR = 97, INDENT = 98, DEDENT = 99
  };

  Python3Lexer(antlr4::CharStream *input);
  ~Python3Lexer();


      private:
          // A queue where extra tokens are pushed on (see the NEWLINE lexer rule).
          list<unique_ptr<Token>> Tokens;
          // The stack that keeps track of the indentation level.
          stack<int> Indents;
          // The amount of opened braces, brackets and parenthesis.
          int Opened = 0;
          // The most recently produced token.
          unique_ptr<Token> LastToken;

      public:
          void emit(unique_ptr<Token> token)
          {
              setToken(move(token));
              Tokens.push_back(move(token));
          }

      private:
          CommonToken* commonToken(size_t type, string text)
          {
              int stop = this->getCharIndex() - 1;
              int start = text.length() == 0 ? stop : stop - text.length() + 1;
              return new CommonToken(this->_tokenFactorySourcePair, type, DEFAULT_TOKEN_CHANNEL, start, stop);
          }

      public:
          unique_ptr<Token> createDedent()
          {
              CommonToken* dedent = new CommonToken(DEDENT, "");
              dedent->setLine(LastToken->getLine());
              Token* obj = dedent;
              unique_ptr<Token> ptr(obj);
              return ptr;
          }

          unique_ptr<Token> nextToken()
          {
              // Check if the end-of-file is ahead and there are still some DEDENTS expected.
              if (_input->LA(1) == EOF && this->Indents.size() != 0)
              {
                  // Remove any trailing EOF tokens from our buffer.
                  for(auto ptr = Tokens.begin(); ptr != Tokens.end(); ptr++) {
                      if((*ptr)->getType() == EOF) {
                          Tokens.erase(ptr);
                      }
                  }
                  Token* obj = commonToken(NEWLINE, "\n");
                  unique_ptr<Token> uptr(obj);
                  // First emit an extra line break that serves as the end of the statement.
                  emit(move(uptr));

                  // Now emit as much DEDENT tokens as needed.
                  while (Indents.size() != 0)
                  {
                      emit(createDedent());
                      Indents.pop();
                  }

                  // Put the EOF back on the token stream.
                  obj = commonToken(EOF, "<EOF>");
                  unique_ptr<Token> uptr2(obj);
                  emit(move(uptr2));
              }

              auto next = nextToken();
              if (next->getChannel() == DEFAULT_TOKEN_CHANNEL)
              {
                  // Keep track of the last token on the default channel.
                  LastToken = move(next);
              }

              if (Tokens.size() == 0)
              {
                  return next;
              }
              else
              {
                  auto x = move(Tokens.back()); Tokens.pop_back();
                  return x;
              }
          }

          // Calculates the indentation of the provided spaces, taking the
          // following rules into account:
          //
          // "Tabs are replaced (from left to right) by one to eight spaces
          //  such that the total number of characters up to and including
          //  the replacement is a multiple of eight [...]"
          //
          //  -- https://docs.python.org/3.1/reference/lexical_analysis.html#indentation
          static int getIndentationCount(string spaces)
          {
              int count = 0;
              char charArray[spaces.length()];
              strcpy(charArray, spaces.c_str());
              for(char ch : charArray)
              {
                  count += ch == '\t' ? 8 - (count % 8) : 1;
              }
              return count;
          }

          bool atStartOfInput()
          {
              return getCharPositionInLine() == 0 && getLine() == 1;
          }

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

  virtual void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;
  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.
  void NEWLINEAction(antlr4::RuleContext *context, size_t actionIndex);
  void OPEN_PARENAction(antlr4::RuleContext *context, size_t actionIndex);
  void CLOSE_PARENAction(antlr4::RuleContext *context, size_t actionIndex);
  void OPEN_BRACKAction(antlr4::RuleContext *context, size_t actionIndex);
  void CLOSE_BRACKAction(antlr4::RuleContext *context, size_t actionIndex);
  void OPEN_BRACEAction(antlr4::RuleContext *context, size_t actionIndex);
  void CLOSE_BRACEAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.
  bool NEWLINESempred(antlr4::RuleContext *_localctx, size_t predicateIndex);

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

