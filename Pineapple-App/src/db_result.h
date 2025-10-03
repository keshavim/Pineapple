/// Wraps query results with both raw access and formatted printing.
#include "nanodbc/nanodbc.h"
class DBResult
{
public:
    DBResult();
    explicit DBResult(nanodbc::result &r);

    std::optional<std::string> get(size_t row, size_t col) const;
    size_t rowCount() const;
    size_t colCount() const;
    std::string toString() const;

private:
    std::vector<std::string> columnNames_;
    std::vector<std::vector<std::string>> data_;
};
