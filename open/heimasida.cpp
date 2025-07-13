from string import digits, ascii_letters
x = input()
replacements = {
    "Á": "a",
    "á": "a",
    "É": "e",
    "é": "e",
    "Í": "i",
    "í": "i",
    "Ó": "o",
    "ó": "o",
    "Ú": "u",
    "ú": "u",
    "Ý": "y",
    "ý": "y",
    "Ö": "o",
    "ö": "o",
    "æ": "ae",
    "Æ": "ae",
    "þ": "th",
    "Þ": "th",
    "Ð": "d",
    "ð": "d",
}
for a,b in replacements.items():
    x = x.replace(a,b)
res = []
for c in x:
    if c in digits + ascii_letters:
        res.append(c)
x="".join(res)
print(f"{x.lower()}.is")

