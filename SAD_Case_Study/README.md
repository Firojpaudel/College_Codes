
# Productivity Tracker Software ⏰

## Introduction
This is a **Productivity Tracker Software** designed to help users manage tasks efficiently and stay focused using the Pomodoro technique. The application allows users to:
- Sign up and log in.
- Add and manage tasks.
- Track time spent on tasks using Pomodoro sessions.
- View task progress and performance through simple, intuitive interfaces.

## Getting Started

### Step 1: Clone the College Repository

To get started with the project, clone the college's repository to your local machine:

```bash
git clone https://github.com/Firojpaudel/College_Codes.git

cd SAD_Case_Study
```

### Step 2: Install Required Libraries

Make sure you have Python 3.8+ installed on your system. Then, install the required dependencies for the project:

```bash
pip install -r requirements.txt
```

### Step 3: Create the Database

Before running the project, you need to set up the SQLite database. Run the following script to create the database file:

```bash
cd Db_codes

python database_create.py
```

This will create a `productivity.db` file in your project directory, which will be used by the application to store tasks and session data.

### Step 4: Running the Pomodoro Timer

Now, you are ready to run the project. To start the Pomodoro session and manage tasks, run:

```bash
cd ..
python pomodoro.py
```

This will start the Pomodoro timer, allowing you to interact with the application, manage tasks, and track your time.

## Project Structure

- **database_create.py**: Creates the SQLite database and the necessary tables.
- **pomodoro.py**: Runs the main Pomodoro timer application for task tracking.
- **productivity.db**: SQLite database where user data, tasks, and session logs are stored.

## Dependencies
- `sqlite3`: For database interactions.
- `time`: For managing the Pomodoro timer duration.
- `getpass`: For securely handling user passwords during login/signup.
- `datetime`: For tracking timestamps during task creation and sessions.
- `hashlib`: For hashing passwords for secure storage.

## Flow of Execution

1. **Database Setup**: 
    - First, run `database_create.py` to set up the database.
    - This will create the `productivity.db` file with tables for users, tasks, and sessions.
   
2. **Running the Application**: 
    - Execute `pomodoro.py` to start using the software. 
    - Log in or sign up, then manage tasks, start Pomodoro sessions, and track your productivity.

<div align="center">
    <img src="https://i.postimg.cc/j5yh96H7/overall.png" width="300px">
</div>


---

## Future Updates & Scalability

- **Future Features**: We plan to integrate features such as:
  - User notifications for overdue tasks.
  - Data analytics and performance reports for task tracking.
  
- **Scalability**: The app is designed to scale to include more users, tasks, and advanced features such as cloud sync.

## Maintenance

Regular updates and bug fixes will be made to improve user experience, ensure compatibility with newer Python versions, and add requested features.

---
