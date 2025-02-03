import sqlite3
import time
from getpass import getpass
from datetime import datetime
import hashlib
import sys

# ==================== Database Connection ====================
def connect_db():
    return sqlite3.connect('productivity.db')


# ==================== Password Hashing ====================
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()


# ==================== Signup & Login ====================
def signup():
    print("\n--- 📝 Sign Up ---")
    username = input("Choose a username: ")
    password = getpass("Choose a password: ")
    confirm_password = getpass("Confirm password: ")

    if password != confirm_password:
        print("❌ Passwords do not match. Please try again.")
        return None

    hashed_password = hash_password(password)

    conn = connect_db()
    cursor = conn.cursor()

    try:
        cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed_password))
        conn.commit()
        print(f"✅ User '{username}' registered successfully!")
        return cursor.lastrowid
    except sqlite3.IntegrityError:
        print("❌ Username already exists. Please try a different one.")
    finally:
        conn.close()
    return None


def login():
    print("\n--- 🔐 Login ---")
    username = input("Enter username: ")
    password = getpass("Enter password: ")

    hashed_password = hash_password(password)

    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, hashed_password))
    user = cursor.fetchone()
    conn.close()

    if user:
        print(f"✅ Login successful! Welcome, {username}!")
        return user[0]  # User ID
    else:
        print("❌ Login failed. Invalid username or password.")
        return None


# ==================== Task Management ====================
def display_tasks(user_id):
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM tasks WHERE user_id=?', (user_id,))
    tasks = cursor.fetchall()
    conn.close()

    print("\n📋 Your Tasks:")
    print("=" * 40)
    if tasks:
        for task in tasks:
            print(f"ID: {task[0]} | Title: {task[1]} | Status: {task[4]}")
    else:
        print("No tasks found.")
    print("=" * 40)


def add_task(user_id):
    print("\n--- ➕ Add Task ---")
    title = input("Task title: ")
    description = input("Task description: ")
    due_date = input("Due date (YYYY-MM-DD): ")

    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO tasks (title, description, due_date, status, created_at, updated_at, user_id)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    ''', (title, description, due_date, 'pending', datetime.now(), datetime.now(), user_id))

    conn.commit()
    conn.close()
    print("✅ Task added successfully!")


def update_task(user_id):
    display_tasks(user_id)
    task_id = int(input("Enter Task ID to update: "))
    status = input("New status (pending, in_progress, completed): ")

    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('''
        UPDATE tasks SET status=?, updated_at=? WHERE id=? AND user_id=?
    ''', (status, datetime.now(), task_id, user_id))

    conn.commit()
    conn.close()
    print("✅ Task updated successfully!")


# ==================== Pomodoro Timer with Animation ====================
def pomodoro_animation(duration):
    total_ticks = 30  # Length of the progress bar
    interval = duration / total_ticks

    print("\n⏳ Pomodoro Timer: [", end="", flush=True)
    for i in range(1, total_ticks + 1):
        time.sleep(interval)
        percentage = int((i / total_ticks) * 100)
        
        # Dynamic progress bar with percentage and timer emoji
        progress_bar = "█" * i + "-" * (total_ticks - i)
        print(f"\r⏳ Pomodoro Timer: [{progress_bar}] {percentage}% ⏱️", end="", flush=True)

    # Completed progress bar with 100% and check mark
    print(f"\r⏳ Pomodoro Timer: [{'█' * total_ticks}] 100% ✅")


def pomodoro_timer(user_id):
    display_tasks(user_id)
    task_id = int(input("Enter Task ID to start Pomodoro timer: "))

    print("\n🍅 Pomodoro session started! Focus for 1 minute.")
    start_time = datetime.now()

    pomodoro_animation(1 * 60)  # 25-minute timer with animation

    end_time = datetime.now()

    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO sessions (task_id, activity, start_time, end_time, date)
        VALUES (?, ?, ?, ?, ?)
    ''', (task_id, 'Pomodoro session', start_time, end_time, datetime.now()))

    conn.commit()
    conn.close()

    print(f"\n✅ Pomodoro session for Task ID {task_id} completed!")


# ==================== Main CLI Interface ====================
def main_menu(user_id):
    while True:
        print("\n--- 📊 Task Tracker Menu ---")
        print("[1] 📋 Display Tasks")
        print("[2] ➕ Add Task")
        print("[3] ✏️ Update Task")
        print("[4] ⏱️ Start Pomodoro Timer")
        print("[5] 🚪 Logout")
        print("[6] ❌ Exit")

        choice = input("Choose an option: ")

        if choice == '1':
            display_tasks(user_id)
        elif choice == '2':
            add_task(user_id)
        elif choice == '3':
            update_task(user_id)
        elif choice == '4':
            pomodoro_timer(user_id)
        elif choice == '5':
            print("🔒 Logged out successfully!")
            return  # Go back to the login/signup menu
        elif choice == '6':
            print("👋 Goodbye!")
            sys.exit()
        else:
            print("❌ Invalid option. Please try again.")


def main():
    print("=" * 40)
    print("📊 Welcome to the Task Tracker CLI 📊")
    print("=" * 40)

    while True:
        choice = input("\n[1] 🔐 Login\n[2] 📝 Sign Up\n[3] ❌ Exit\nChoose an option: ")

        if choice == '1':
            user_id = login()
            if user_id:
                main_menu(user_id)
        elif choice == '2':
            user_id = signup()
            if user_id:
                main_menu(user_id)
        elif choice == '3':
            print("👋 Goodbye!")
            return
        else:
            print("❌ Invalid option. Please try again.")


if __name__ == "__main__":
    main()