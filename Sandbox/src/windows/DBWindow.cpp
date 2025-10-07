#include "DBWindow.h"


DBWindow::DBWindow(const std::string &title) :
    m_Title(title),
    m_Table("DBResultTable")
{
    // Connect to DB
    //authentication will be handled in gui later
    std::string user;
    std::cout << "user: ";
    std::getline(std::cin, user);

    std::string password;
    std::cout << "password: ";
    std::getline(std::cin, password);
    //this will really need to change
    auto ok = pap::DBManager::connect(pap::DBDriver::MariaDB, "tcp://127.0.0.1:3306", user, password, "students");

    //todo: make gui
    if (!ok)
    {
        PAP_INFO("failed");
        return;
    }
    std::cout << "[DEBUG] Running query: SELECT * FROM student_info;" << std::endl;
    auto test = pap::DBManager::executeQuery("SELECT * FROM student_info;");
    if (!test)
    {
        std::cout << "aFailed query: " << test.error() << "\n";
        return;
    }
    m_Result = *test;


    // Configure your table flags
    m_Table.setFlags(
        pap::Table_Resizable |
        pap::Table_Sortable |
        pap::Table_Borders |
        pap::Table_RowBg |
        pap::Table_Foldable |
        pap::Table_AutoResize
    );
}

void DBWindow::drawImGui()
{
    ImGui::Begin(m_Title.c_str());

    // Set columns if not set yet (or every frame if dynamic)
    m_Table.setColumns(m_Result.getColumnNames());

    // Populate table data
    std::vector<std::vector<std::string>> rows;
    for (size_t r = 0; r < m_Result.getRowCount(); ++r)
    {
        auto rowRes = m_Result.getRow(r);
        rows.push_back(pap::unwrap_or_else(rowRes, [](const std::string& err){
            std::cerr << "Failed to get row: " << err << "\n";
            return std::vector<std::string>{};
        }));
    }

    m_Table.setData(rows);

    // Draw table
    m_Table.draw();

    ImGui::End();
}
