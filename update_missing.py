#!/usr/bin/env python3
"""Regenerate the list of problems solved on Open Kattis but missing from open/.

Fast path (default): diff the local open/ folder against the cached solved list
(solved_kattis.txt). Open Kattis is NOT contacted.

    python3 update_missing.py

Refresh path: re-fetch the solved list from the Kattis profile, rewrite the
cache, then diff. Use after solving new problems on Kattis.

    python3 update_missing.py --refresh

Cookie (refresh only): $KATTIS_COOKIE or ~/.cache/kattis_cookie.txt (value of
the KattisSiteCookie session cookie). User defaults to joshua-andersson.
"""
import os, re, sys, datetime

USER = os.environ.get("KATTIS_USER", "joshua-andersson")
HERE = os.path.dirname(os.path.abspath(__file__))
OPEN_DIR = os.path.join(HERE, "open")
CACHE = os.path.join(HERE, "solved_kattis.txt")
OUT = os.path.join(HERE, "missing_kattis.md")


# --- refresh: scrape solved problems from the Kattis profile ------------------
def cookie():
    c = os.environ.get("KATTIS_COOKIE")
    if c:
        return c.strip()
    with open(os.path.expanduser("~/.cache/kattis_cookie.txt")) as f:
        return f.read().strip()


def solved_on_page(html):
    """Slugs from the *solved* table only: drop the recent-submissions table
    (after 'Group / Team') and the page-1 'recommended' table (Not Attempted)."""
    head = html.split("Group / Team", 1)[0]
    ids = set()
    for tbl in re.findall(r"<table.*?</table>", head, re.S):
        if "Not Attempted" in tbl or "is-status-" in tbl:
            continue
        ids |= {m for m in re.findall(r'/problems/([a-z0-9._]+)"', tbl)
                if not m.endswith("/statistics")}
    return ids


def refresh():
    import urllib.request
    ck = cookie()
    solved, empty, page = set(), 0, 1
    while empty < 2 and page < 60:
        url = f"https://open.kattis.com/users/{USER}?tab=problems&page={page}"
        req = urllib.request.Request(url, headers={
            "Cookie": f"KattisSiteCookie={ck}", "User-Agent": "Mozilla/5.0"})
        with urllib.request.urlopen(req, timeout=40) as r:
            ids = solved_on_page(r.read().decode("utf-8", "replace"))
        if ids:
            solved |= ids; empty = 0
        else:
            empty += 1
        page += 1
    if not solved:
        sys.exit("No solved problems parsed — cookie likely expired. "
                 "Refresh ~/.cache/kattis_cookie.txt (KattisSiteCookie value).")
    with open(CACHE, "w") as f:
        f.write("\n".join(sorted(solved)) + "\n")
    return solved


# --- diff ---------------------------------------------------------------------
def load_solved():
    with open(CACHE) as f:
        return {l.strip() for l in f if l.strip()}


def load_local():
    return {re.sub(r"\.(cpp|py)$", "", f) for f in os.listdir(OPEN_DIR)}


def columns(items, ncol=3):
    items = sorted(items)
    rows = (len(items) + ncol - 1) // ncol
    grid = [items[i*rows:(i+1)*rows] for i in range(ncol)]
    w = max((len(x) for x in items), default=0) + 3
    out = []
    for r in range(rows):
        out.append("".join(grid[c][r].ljust(w) for c in range(ncol)
                            if r < len(grid[c])).rstrip())
    return "\n".join(out)


def main():
    solved = refresh() if "--refresh" in sys.argv else load_solved()
    local = load_local()
    missing = solved - local
    body = (f"# Solved on Open Kattis but missing from open/\n\n"
            f"_Updated {datetime.date.today()} | user {USER} | "
            f"solved {len(solved)} | local {len(local)} | "
            f"missing {len(missing)}_\n\n```\n{columns(missing)}\n```\n")
    with open(OUT, "w") as f:
        f.write(body)
    print(f"solved={len(solved)} local={len(local)} missing={len(missing)}")
    print(f"written: {OUT}")


if __name__ == "__main__":
    main()
