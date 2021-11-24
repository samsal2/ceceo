target_sources(${PROJECT_NAME} PRIVATE 
  atom.hpp
  context.cpp
  context.hpp
  interpreter.cpp
  interpreter.hpp
  main.cpp
  number.hpp
  parser.cpp
  parser.hpp
  source_range.hpp
  symbol.hpp
  token.hpp
  tokenizer.cpp
  tokenizer.hpp)


add_subdirectory(ast)
