# pipex

Ever wondered what actually happens when you type a `|` (pipe) in your terminal?

Before this project, I just knew it pushed data from one command to another. **pipex** is the 42 project where you pull back the curtain and recreate that exact shell magic completely from scratch in C.

No shell shortcuts, no cheats. Just processes, file redirections, and learning how Unix moves data around under the hood.

---

### What it does

In plain English, it mimics this classic bash pipeline:

```bash
< infile cmd1 | cmd2 > outfile

```

You run it like this:

```bash
./pipex infile "grep something" "wc -l" outfile

```

Here is what happens behind the scenes:

1. It opens `infile` and feeds its contents into `grep something`.
2. Instead of printing the matches on your screen, it catches that output and hands it directly to `wc -l`.
3. It takes the final count from `wc -l` and writes it into `outfile`.

---

### Chaining Multiple Commands

Beyond the basic two-command setup, this version handles an arbitrary number of pipes:

```bash
./pipex infile "cat" "grep error" "sort" "uniq -c" outfile

```

Which works just like running:

```bash
< infile cat | grep error | sort | uniq -c > outfile

```

---

### How it works (without the heavy jargon)

Getting programs to talk to each other cleanly comes down to four key ideas:

* **Forking (`fork`):** The program clones itself so each command can run in its own independent process at the same time.
* **The Pipe (`pipe`):** A temporary unidirectional tunnel in memory. One command writes data into one end, and the next command sits on the other end reading it.
* **Rerouting (`dup2`):** By default, a command reads from your keyboard and writes to your screen. `dup2` quietly redirects those inputs and outputs to files or pipes instead.
* **Running the Command (`execve`):** Searches your system's `PATH` to find the real executable (like `/usr/bin/grep`) and runs it inside the child process.

---

### The headaches (and what I learned)

* **The infinite freeze:** If you leave even a single write-end of a pipe open, the next command keeps waiting forever for input that will never arrive. Closing unused file descriptors at the exact right moment is half the battle.
* **Zombie processes:** If a child process finishes and the parent never checks in on it, it lingers in memory like a ghost. `waitpid` keeps the process table clean.
* **Matching Bash errors:** What happens if `infile` doesn't exist? What if a command is misspelled? Replicating bash's exact error messages and exit codes takes way more attention to detail than the pipes themselves.

---

### Quick Start

**1. Clone and compile:**

```bash
git clone https://github.com/your-username/pipex.git
cd pipex
make

```

**2. Test it out:**

```bash
# Create a quick test file
echo -e "apple\nbanana\napple\norange" > fruits.txt

# Run pipex
./pipex fruits.txt "grep apple" "wc -l" result.txt

# Inspect the result
cat result.txt

```

---

### Author

Built by `aelbouss`. Feel free to star the repo or reach out if you have any questions!