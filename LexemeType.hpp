enum LexemeType {
  integer,
  decimal,
  identifier,
  special,
  reserved,
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
    case reserved:
      return "reserved";
    default:
      return "";
  }
}