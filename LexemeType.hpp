enum LexemeType {
  integer,
  decimal,
  identifier,
  special,
  reserved,
  error,
  comment
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
    case comment:
      return "comment";
    default:
      return "";
  }
}