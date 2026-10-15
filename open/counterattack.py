joshua_hp, rasmus_hp, m, n = map(int, input().split())

attack_j = sorted(list(map(int,input().split())))
attack_r = sorted(list(map(int,input().split())))

n_walls = sum(1 if a == 0 else 0 for a in attack_r)
attack_r = [i for i in attack_r if i != 0]
n = len(attack_r)

tot_attack_j = sum(attack_j)
tot_attack_r = sum(attack_r)
topk_joshua_attack = sum(attack_j[-n_walls:] if n_walls else [])
blocker_strength = 0
attack_strength = 0 # Rasmus
for i in range(m+1):
    n_block = i
    n_attack = m-n_block
    if (tot_attack_r - attack_strength) < joshua_hp:
        if n_attack > n_walls:
            my_attack = tot_attack_j - blocker_strength - topk_joshua_attack
            rasmus_heal = tot_attack_r - attack_strength
            if my_attack >= rasmus_hp + rasmus_heal:
                print("YES")
                exit(0)

    if i < m:
        blocker_strength += attack_j[i]

    rev_idx = n-1-i
    if rev_idx >= 0:
        attack_strength += attack_r[rev_idx]

print("NO")
