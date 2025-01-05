# 📝 Task Manager with Google Drive Integration

A simple command-line task manager written in C++ with functionality to interact with Google Drive for file uploads and updates. This project demonstrates task management, automation, and integration with Google APIs using `curl` and `libcurl`.

---

## ✨ Features

1. 🗂️ **Task Management**:

   - Add, view, and remove tasks.
   - Save and load tasks from a file (`tasks.txt`).

2. ☁️ **Google Drive Integration**:

   - Upload and update files on Google Drive.
   - Automatic conversion of Word documents to PDF before upload.

3. 🔗 **Link Shortcuts**:

   - Open frequently used links or projects via simple shortcuts.

4. 🚀 **Dynamic Command Execution**:
   - Automates system commands for quick project and resource access.

---

## 📂 Project Structure

- **📝 Task Management**: Handles adding, viewing, and removing tasks from a list.
- **📤 File Management**:
  - Converts Word files to PDF using system commands.
  - Uses `curl` to upload PDFs to Google Drive.
- **🔗 Shortcut Links**: Allows quick access to predefined project links.

---

## 🛠️ Setup and Requirements

### Prerequisites

- **🖥️ C++ Compiler**: Compatible with C++11 or higher.
- **🔗 curl**:
  - Command-line `curl` installed and accessible in the system's PATH.
  - Alternatively, `libcurl` for direct HTTP integration.
- **📄 Google Drive API**:
  - A project set up in the [Google Cloud Console](https://console.cloud.google.com/).
  - OAuth 2.0 credentials (Client ID, Client Secret, and Refresh Token).
- **🖹 Microsoft Word** (optional): For Word-to-PDF conversion on Windows.

---

### 🛠️ Installation

1. **📥 Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/task-manager-with-drive.git
   cd task-manager-with-drive
   ```
