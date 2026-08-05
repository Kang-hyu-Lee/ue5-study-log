# Session Workflow & GitHub Setup

## 0. One-Time GitHub Setup (do this before Session 1)

You don't need to understand Git deeply yet — just these commands, muscle-memory style. You'll actually *understand* Git properly later as a dedicated topic (it's one of the pillars in your mentor prompt).

1. **Create a GitHub account** → github.com → Sign up.
2. **Install Git locally** → git-scm.com/downloads. Windows: installs "Git Bash" (use this terminal). Mac: often preinstalled — check by typing `git --version` in Terminal; if missing, install via `brew install git` or the installer on the site.
3. **Tell Git who you are** (one-time, in any terminal):
   ```
   git config --global user.name "Your Name"
   git config --global user.email "your-github-email@example.com"
   ```
4. **Create the repository** on GitHub.com → "+" (top right) → New repository → name it `ue5-study-log` → check "Add a README" → Create repository. (Public is fine — this becomes portfolio-visible later; keep it private only if that makes you more comfortable starting out, you can flip it public anytime.)
5. **Clone it to your computer**: on the repo page, click the green "Code" button → copy the HTTPS URL → in your terminal:
   ```
   git clone https://github.com/yourname/ue5-study-log.git
   cd ue5-study-log
   ```
6. **Create the folder structure** your mentor prompt expects:
   ```
   mkdir -p Study/Concepts Study/Exercises Study/Solutions
   ```
7. **Test the full cycle once** so you trust it:
   ```
   git add README.md
   git commit -m "initial setup"
   git push
   ```
   Refresh the GitHub page — you should see it reflected. That's the whole loop you'll repeat every session.

### Daily Git Cheat Sheet (the only 4 commands you need for now)
| Command | What it does |
|---|---|
| `git status` | Shows what changed since your last commit — check this first, always. |
| `git add <path/to/file>` | Stages ONE specific file (never `git add .` — your mentor prompt enforces this so you always know exactly what you're committing and why). |
| `git commit -m "message"` | Saves a snapshot with a description. Message convention: `"day 12: linked lists concept + exercise"`. |
| `git push` | Uploads your commits to GitHub. |

### One thing to set up now, use later: `.gitignore`
Once you start UE5 projects (not yet, but soon), Unreal generates huge folders you should never commit (compiled binaries, caches). Before your first UE5 project push, create a file named `.gitignore` in that project's root containing:
```
Binaries/
Intermediate/
Saved/
DerivedDataCache/
*.sln
```
This isn't needed for the pure C++/math phase — flagging it now so it's not a surprise later.

### Software you'll also need (separate from Git)
- **VS Code** — for C++ fundamentals phase (lightweight, fast to open).
- **Visual Studio Community** (the full IDE, not VS Code) with the **"Game development with C++"** workload — required to compile UE5 C++ projects later. Install this before Phase 2 (week 5+), not now.
- **Unreal Engine 5** itself, via Epic Games Launcher — also a Phase 2 install, no rush.

---

## 1. Session Start Prompt (paste this to open every session)

```
Session: [date] — [Day] — [Foundations focus] / [Applied focus] per schedule.

Recall check (from memory, no notes): <write 2–3 lines on what you remember from last session>

Today's first task (set at end of last session): <paste it>

Begin foundations block.
```

If it's your very first session ever, skip the recall check and just say:
```
Session 1 — Monday — Math foundations / C++ syntax fundamentals. Starting from zero. Begin.
```

## 2. Session End Prompt (paste this to close every session)

```
Wrap session. Give me:
1. Session log summary (learned / confused / one open question) — I'll paste this into my repo log.
2. Exact git add + commit commands for today's files.
3. Tomorrow's first task.
4. Portfolio/interview note if today's work is relevant.
```

## 3. Keeping a Progress Log (do this every session, takes 1 minute)
In your repo, keep one running file: `Study/log.md`. After each session, append the 3-line summary Claude gives you at wrap-up:
```
## Day 12 — 2026-08-05
Learned: linked list insertion/deletion, pointer basics
Confused: why we need a dummy head node
Open question: when to use a doubly vs singly linked list
```
This becomes your evidence of consistency (useful for you) and, later, a readable story of your growth (useful for interviews — "walk me through your learning process" is a real question).

## 4. Weekly (Sunday) — already established
15-min review: what did I retain unaided, what did I "vibe" through and need to repeat, is this week's Saturday project explainable in an interview. No new prompt needed — just answer those honestly in your log.

## 5. Things easy to miss
- **Don't create a new GitHub repo per topic.** One `ue5-study-log` repo, organized by folder, for the whole foundations phase. Split into a separate `portfolio` repo only once you have actual UE5 projects worth showcasing (Phase 2+).
- **Commit even on bad days.** A half-finished exercise committed with an honest message ("day 9: stuck on recursion, partial attempt") is more valuable long-term than nothing — it's real evidence of the process, and it keeps the daily habit unbroken.
- **Don't edit old Concepts files to "fix" your past understanding.** Add a note or a new dated entry instead. Seeing your own past confusion and how it resolved is part of what makes this useful later.
- **Resist the urge to skip the recall check when you're tired.** It's the shortest block and the easiest to cut — it's also the one doing the most work against vibe-coding relapse.
