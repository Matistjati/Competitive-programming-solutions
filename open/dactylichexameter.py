import re
print("yes" if re.fullmatch("^(-uu|--){5}(-u|--)$",input()) else "no")
