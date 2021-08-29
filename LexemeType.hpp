enum LexemeType {
  integer,
  decimal,
  identifier,
  special,
  error,
};

static std::string lexem_type_to_string(LexemeType type) {
    switch (type) {
    case integer:
      return "integer";
    case decimal:
      return "decimal";
    case identifier:
      return "identifier";
    case special:
      return "special";
    case error:
      return "error";
    default:
      return "";
  }
}