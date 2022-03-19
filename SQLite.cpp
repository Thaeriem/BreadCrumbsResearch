

//SELECT last_visit_time, datetime(last_visit_time / 1000000 - 11644473600, _
//'unixepoch', 'localtime'),url,title FROM urls ORDER BY last_visit_time 

typedef struct _SGBrowserHistory
    {
    int Browser;  // 1 = chrome, 2 = firefox, 3 = ie
    WCHAR SiteURL[URL_MAXSIZE];
    WCHAR SiteName[1024];
    WCHAR LastVisitDate[256];
    } SGBrowserHistory;

bool SGBrowsingHistory::GetChromeHistory (SGBrowserHistoryArray *history, CString FileName,CString SearchString) {
    bool result = false;
    WCHAR szPath[MAX_PATH];
    //const char *lpTail;
    utils::SG_GetSpecialFolderPath(szPath, CSIDL_LOCAL_APPDATA);
    StrCat(szPath, CHROMEHISTORY);

    WCHAR filename[MAX_PATH + 1] = { TEMP_DB_NAME };

    if (CopyFile(szPath, filename, FALSE))
    {
        if (GetFileAttributes(filename) != 0xFFFFFFFF){}
        else{
            wprintf(L"Error: Cannot find login data for Google Chrome browser\r\n");
        }
        bool result = db->GetChromeHistoryRecords(filename, history, SearchString);
    }
    return result;
}

#define createTableChromeHistory L"CREATE TABLE IF NOT EXISTS ChromeHistory(\
id INTEGER PRIMARY KEY AUTOINCREMENT,\
created TIMESTAMP not null default CURRENT_TIMESTAMP,\
date_last_visited TEXT not null default '',\
site_name TEXT not null default '',\
size_url TEXT not null default '',\
);"

#define STR_ERROR_RUNNING_QEURY L"Error running query: %s. Error message: %s. Function = %s\n"

void CSGDatabase::LogSqlError(CppSQLite3Exception &e, CString Function, CString sql)
{
    wprintf(STR_ERROR_RUNNING_QEURY, sql.GetBuffer(), e.errorMessage(), Function.GetBuffer());
}

// convert chrome time (as long long integer) to system time
SYSTEMTIME intChromeTimeToSysTime(long long int UnixTime)
{
    time_t dosTime(UnixTime);
    // Note that LONGLONG is a 64-bit value
    SYSTEMTIME systemTime;


    LARGE_INTEGER utcFT = { 0 };
    utcFT.QuadPart = ((unsigned __int64)dosTime) * 10000000;

    FileTimeToSystemTime((FILETIME*)&utcFT, &systemTime);
    return systemTime;
}

int main() {
    #define CHROME_HISTORY_SQL_QUERY2_LEFT "SELECT last_visit_time, 
    datetime(last_visit_time / 1000000 - 11644473600, 'unixepoch', 'localtime'),
    url,title FROM urls WHERE title like '"

    #define CHROME_HISTORY_SQL_QUERY2_RIGHT "' ORDER BY last_visit_time DESC"

    Fetch history based on a complex query

    typedef CSimpleArray<SGBrowserHistory> SGBrowserHistoryArray;
}