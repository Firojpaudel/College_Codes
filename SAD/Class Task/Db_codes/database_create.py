import sqlite3

# Connect to SQLite database
con = sqlite3.connect('productivity.db')
cursor = con.cursor()

# Enable foreign key support
cursor.execute('PRAGMA foreign_keys = ON;')

# Create users table
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
)
''')

# Create tasks table with user_id as a foreign key
cursor.execute('''
CREATE TABLE IF NOT EXISTS tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    description TEXT,
    due_date TEXT,
    status TEXT CHECK(status IN ('pending', 'in_progress', 'completed')) DEFAULT 'pending',
    created_at TEXT,
    updated_at TEXT,
    user_id INTEGER,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
)
''')

# Create sessions table
cursor.execute('''
CREATE TABLE IF NOT EXISTS sessions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    task_id INTEGER,
    activity TEXT,
    start_time TEXT,
    end_time TEXT,
    date TEXT,
    FOREIGN KEY (task_id) REFERENCES tasks(id) ON DELETE CASCADE
)
''')

con.commit()
con.close()

print("Database and tables created successfully!")
