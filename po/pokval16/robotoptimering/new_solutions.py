#!/usr/bin/env python3
# AC 100 submission for new version of robotoptimering
# Horribly formatted. Can you beat this? In that, please
# send me an email to <github_username>@outlook.com
ans = {

'robot_concentric': """
main:
        right
        segs:
        forward
        left
        gotoblocked segs
        for 4 {
                forward
                gotoblocked main
                left
        }


        """,'robot_cross': """main:

    right

    for 125 {

            gotoblocked main

            forward

            left

    }

    call main

""",'robot_diagonal': """main:

    right

    segs:

    gotoblocked main

    forward

    left

    call segs

""",'robot_ew_manuell': """main:
        right
        for 6 {
                forward
                left
                gotoblocked segs
        }
        segs:
        right
        call main

""",'robot_path_freedom': """main:

    right

    segs:

    gotoblocked main

    forward

    left

    call segs

""",'robot_path_freedom2': """main:

    segs:

    left

    for 32 {

            left

            for 21 {

                    forward

                    left

                    forward

                    right

            }

    }

    call segs""",'robot_rand_60': """lft:
    right
wall:
    gotoblocked lft
    return
 
main:
    for 128188 {
        call wall
        forward
        left
    }
    left
    call main

        """,'robot_rand_80': """segs:
    right
    gotoblocked segs
    forward
main:
    left
    zero:
    gotoblocked segs
    forward
    left
    for 17 {
        forward
    }
    right
    call zero





""",'robot_maze': """main:

    right

    segs:

    gotoblocked main

    forward

    left

    call segs

""",'robot_spiral': """main:

    for 1000 {

        forward

    }

    left

    call main""",}

casename = input()

print (ans[casename])