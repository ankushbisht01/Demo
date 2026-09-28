# The Ultimate Git Commands Cheat Sheet
*A complete reference guide from basics to advanced workflows and emergency recovery.*

---

## Table of Contents
1. [Initial Setup & Configuration](#1-initial-setup--configuration)
2. [Starting a Repository](#2-starting-a-repository)
3. [Basic Daily Workflow (Add, Commit, Status)](#3-basic-daily-workflow)
4. [Inspecting Differences & History](#4-inspecting-differences--history)
5. [Branching & Switching](#5-branching--switching)
6. [Merging & Rebasing](#6-merging--rebasing)
7. [Working with Remotes (GitHub, GitLab)](#7-working-with-remotes)
8. [Stashing (Temporary Storage)](#8-stashing-temporary-storage)
9. [Undoing & Recovery (Reset, Revert, Restore)](#9-undoing--recovery)
10. [Tagging & Releases](#10-tagging--releases)
11. [Advanced Commands (Cherry-Pick, Bisect, Reflog)](#11-advanced-commands)
12. [Common "Oh Shit, Git!" Quick Fixes](#12-common-emergency-fixes)

---

## 1. Initial Setup & Configuration

Configure identity and global defaults once per machine:

```bash
# Set your name and email (used in every commit)
git config --global user.name "Your Name"
git config --global user.email "you@example.com"

# Set default initial branch name to main
git config --global init.defaultBranch main

# Configure line ending handling (Mac/Linux: input, Windows: true)
git config --global core.autocrlf input

# Set your default text editor (e.g. nano, vim, code --wait)
git config --global core.editor "nano"

# View all active configurations
git config --list --show-origin
```

---

## 2. Starting a Repository

```bash
# Initialize a new local Git repository in the current directory
git init

# Initialize with a specific branch name
git init -b main

# Clone an existing remote repository onto your machine
git clone https://github.com/username/repository.git

# Clone into a specific target folder name
git clone https://github.com/username/repository.git my-folder

# Clone only the latest commit (shallow clone for speed/saving disk space)
git clone --depth 1 https://github.com/username/repository.git
```

---

## 3. Basic Daily Workflow

The standard three-stage architecture: **Working Directory $\to$ Staging Area (Index) $\to$ Repository (Commit)**.

```bash
# Check status of modified, staged, and untracked files
git status

# Check status in short/compact format
git status -s

# Stage a specific file
git add filename.txt

# Stage all modified, deleted, and new files in the current directory
git add .

# Stage all tracked modified files (ignores untracked files)
git add -u

# Interactively choose hunks/parts of a file to stage
git add -p

# Commit staged changes with an inline message
git commit -m "feat: add user authentication"

# Stage all tracked modified files AND commit in one step
git commit -am "fix: typo in header"

# Amend / update the most recent commit (e.g. to fix typo in message or add forgotten file)
git add forgotten_file.txt
git commit --amend --no-edit
```

---

## 4. Inspecting Differences & History

```bash
# Show unstaged changes (Working Directory vs. Staging Area)
git diff

# Show staged changes ready to be committed (Staging Area vs. Last Commit)
git diff --staged
# or:
git diff --cached

# Compare changes between two branches
git diff main feature-branch

# View chronological commit history
git log

# Clean, one-line graphical commit history
git log --oneline --graph --decorate --all

# View the last N commits with diff patches
git log -p -2

# Show detailed changes in a specific commit
git show <commit-hash>

# See who modified each line of a file and when
git blame filename.txt
```

---

## 5. Branching & Switching

```bash
# List local branches (* marks current branch)
git branch

# List both local and remote-tracking branches
git branch -a

# Create a new branch (stays on current branch)
git branch feature-login

# Switch to an existing branch
git switch feature-login
# (Legacy alternative):
git checkout feature-login

# Create AND switch to a new branch in one command
git switch -c feature-dashboard
# (Legacy alternative):
git checkout -b feature-dashboard

# Rename current branch to main
git branch -m main

# Rename another branch
git branch -m old-name new-name

# Delete a branch safely (prevents deleting unmerged work)
git branch -d feature-login

# Force delete a branch (even if unmerged)
git branch -D feature-login

# Delete a remote branch on GitHub
git push origin --delete feature-login
```

---

## 6. Merging & Rebasing

Integrate changes from one branch into another:

```bash
# 1. Fast-forward or 3-way Merge
# Switch to target branch first
git switch main
# Merge the feature branch into main
git merge feature-login

# Abort a merge in case of conflicts
git merge --abort

# 2. Rebase (re-apply your commits on top of another branch for a linear history)
git switch feature-login
git rebase main

# During rebase conflict resolution:
git add resolved_file.py
git rebase --continue

# Abort a rebase and return to original state
git rebase --abort

# Interactive Rebase (squash, reword, or delete last 3 commits)
git rebase -i HEAD~3
```

---

## 7. Working with Remotes

```bash
# List all configured remotes with URLs
git remote -v

# Connect local repo to a remote repository
git remote add origin https://github.com/username/repo.git

# Change the URL of an existing remote
git remote set-url origin https://github.com/username/new-repo.git

# Download remote changes without merging into local branches
git fetch origin

# Fetch and automatically merge into current branch
git pull origin main

# Pull using rebase instead of merge commit (cleaner history)
git pull --rebase origin main

# Push commits to remote branch and set upstream tracking (-u)
git push -u origin main

# Standard push after upstream is set
git push

# Force push (WARNING: overwrites remote history; use --force-with-lease to be safer)
git push --force-with-lease
```

---

## 8. Stashing (Temporary Storage)

Save uncommitted work aside without committing:

```bash
# Stash tracked modified changes
git stash

# Stash with a descriptive message
git stash save "WIP: halfway through refactor"

# Stash including untracked files
git stash -u

# View list of saved stashes
git stash list

# Re-apply the most recent stash and remove it from stash list
git stash pop

# Apply a stash without removing it from list
git stash apply stash@{0}

# Inspect what is inside a stash
git stash show -p stash@{0}

# Discard a specific stash
git stash drop stash@{0}

# Delete all stashes
git stash clear
```

---

## 9. Undoing & Recovery

```bash
# Discard unstaged changes in a file (restore working directory to last commit)
git restore filename.py

# Unstage a file (keep local modifications intact)
git restore --staged filename.py
# (Legacy alternative):
git reset HEAD filename.py

# Discard ALL unstaged changes in the entire working directory
git restore .

# Create a new commit that inverts/undoes a previous commit (safe for shared branches)
git revert <commit-hash>

# Soft Reset: Move HEAD back 1 commit, keep changes in Staging Area
git reset --soft HEAD~1

# Mixed Reset (default): Move HEAD back 1 commit, keep changes unstaged in Working Directory
git reset --mixed HEAD~1

# Hard Reset (DANGER): Discard commits, staging, AND uncommitted file changes
git reset --hard HEAD~1

# Remove untracked files and folders
git clean -fd   # -f = force, -d = include directories
```

---

## 10. Tagging & Releases

```bash
# List all tags
git tag

# Create a lightweight tag at current commit
git tag v1.0.0

# Create an annotated release tag with a message
git tag -a v1.0.0 -m "Release version 1.0.0"

# Push a specific tag to remote
git push origin v1.0.0

# Push all local tags to remote
git push origin --tags

# Delete a local tag
git tag -d v1.0.0

# Delete a remote tag
git push origin --delete v1.0.0
```

---

## 11. Advanced Commands

```bash
# 1. Cherry-Pick: Apply a specific single commit from another branch onto current branch
git cherry-pick <commit-hash>

# 2. Reflog: The safety net recording EVERY movement of HEAD (even deleted commits/branches)
git reflog

# Recover a commit that was accidentally hard-reset:
git reset --hard <reflog-hash>

# 3. Bisect: Binary search through history to identify which commit introduced a bug
git bisect start
git bisect bad                 # Current commit is broken
git bisect good v1.0           # Tag/commit known to be working
# Git checks out intermediate commits; you test and run 'git bisect good' or 'git bisect bad'
git bisect reset               # End bisect session
```

---

## 12. Common Emergency Fixes

| Problem | Solution |
| :--- | :--- |
| **"I committed with a typo in the message"** | `git commit --amend -m "new correct message"` |
| **"I forgot to add a file to the last commit"** | `git add forgotten.txt && git commit --amend --no-edit` |
| **"I committed to `main` instead of a feature branch"** | `git branch feature-branch && git reset --hard HEAD~1 && git switch feature-branch` |
| **"I accidentally did `git reset --hard` and lost my work"** | Run `git reflog`, find the hash before reset, then `git reset --hard <hash>` |
| **"I want to discard all local changes and match remote `main`"** | `git fetch origin && git reset --hard origin/main` |
| **"A merge conflict happened"** | Edit marked conflict lines (`<<<<<<<`, `=======`, `>>>>>>>`), then `git add .` and `git commit` (or `git merge --abort` to cancel) |
