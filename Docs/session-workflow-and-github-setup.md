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

Topic decisions are pre-made in `phase1-curriculum-roadmap.md` — you only supply the day number and the recall check.

```
Day [N]. Recall check: <2–3 lines from memory, or "n/a, starting from zero">. Begin.
```

That's the whole prompt. Claude looks up Day N's Foundations/Applied topics in the roadmap file automatically — no other input needed from you.

## 1b. Mid-Session Terminology Flag
Anytime a term comes up you have a vague gist of but not real understanding, write it with a `?` (e.g. `REST API?`, `tick rate?`). This pauses whatever's happening for a brief explanation, then logs it to `Study/glossary.md` at session wrap (see end prompt below). No separate prompt needed — this works inside any session automatically once it's in your Project Instructions (see the addition Claude gave you to append there).

## 2. Session End Prompt (paste this to close every session)

```
Wrap session. Give me:
1. Session log summary (learned / confused / one open question) — I'll paste this into my repo log.
2. Exact git add + commit commands for today's files.
3. Tomorrow's first task.
4. Portfolio/interview note if today's work is relevant.
5. Any glossary terms I flagged with "?" today — logged to Study/glossary.md under the right category.
```
On Sundays, the wrap also generates next week's coding + math practice sheet (see study-schedule.md's Weekly Practice Sheet section) — no separate prompt needed, it's part of the Sunday review wrap.

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

## 4b. Putting These Docs on GitHub (so any monitor/device can pull them up)
Put these three files in a `Docs/` folder in your `ue5-study-log` repo — separate from `Study/` (which holds daily lesson output), since these are standing references, not session content.

Note: `Study/glossary.md` and the weekly `Study/Exercises/` sheets are NOT part of this `Docs/` batch — they live in `Study/` since they're living session content, updated by Claude at session wrap rather than pushed by you as standing references. Same git loop applies (`git add Study/glossary.md`, commit, push), just as part of your normal end-of-session commits rather than a separate Docs push.

1. Download the three files from this chat: `study-schedule.md`, `phase1-curriculum-roadmap.md`, `session-workflow-and-github-setup.md`.
2. Move them into your cloned repo folder, under a new `Docs/` subfolder:
   ```
   cd ue5-study-log
   mkdir -p Docs
   ```
   (then drag/move the three downloaded files into `ue5-study-log/Docs/`)
3. Commit and push each one individually (same one-file-per-commit habit as everything else):
   ```
   git add Docs/study-schedule.md
   git commit -m "add study schedule reference"
   git add Docs/phase1-curriculum-roadmap.md
   git commit -m "add phase 1 curriculum roadmap"
   git add Docs/session-workflow-and-github-setup.md
   git commit -m "add session workflow guide"
   git push
   ```
4. From any other monitor/device, you can now open `github.com/yourname/ue5-study-log/Docs/` in a browser and read them directly — GitHub renders `.md` files nicely with no extra tooling needed. No need to re-clone if you're just reading; only clone on a machine where you'll actually be coding.

If you update these docs later (e.g. Phase 2 roadmap gets added), edit the file, then `git add Docs/<file>`, `git commit -m "update ..."`, `git push` — same loop, just applied to a doc instead of a lesson file.

## 5. Things easy to miss
- **Don't create a new GitHub repo per topic.** One `ue5-study-log` repo, organized by folder, for the whole foundations phase. Split into a separate `portfolio` repo only once you have actual UE5 projects worth showcasing (Phase 2+).
- **Commit even on bad days.** A half-finished exercise committed with an honest message ("day 9: stuck on recursion, partial attempt") is more valuable long-term than nothing — it's real evidence of the process, and it keeps the daily habit unbroken.
- **Don't edit old Concepts files to "fix" your past understanding.** Add a note or a new dated entry instead. Seeing your own past confusion and how it resolved is part of what makes this useful later.
- **Resist the urge to skip the recall check when you're tired.** It's the shortest block and the easiest to cut — it's also the one doing the most work against vibe-coding relapse.
