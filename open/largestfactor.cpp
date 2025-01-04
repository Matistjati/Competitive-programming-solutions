import subprocess
print(max(int(i) for i in subprocess.run(["factor", input()], capture_output=True).stdout.decode().split(": ")[1].split()))

