import subprocess
print(subprocess.run(["factor", input()], capture_output=True).stdout.decode().split(": ")[1])

