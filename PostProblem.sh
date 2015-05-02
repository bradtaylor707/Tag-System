# the axiom is a string of color names: r for red and b for blue; the axiom can be represented by a row of colored eggs...
axiom='rrbrbr'
for n in `seq 1 20`; do
    egg=${axiom:0:3} # for a 3-tag system looks at the 3 first characters
    case ${egg:0:1} in # only the first of the three letters decides what happens next
    # these are the rules chosen by Post (1946)
        'b')
            axiom=$axiom'bb';; # the blue egg yields a blue fish who swims over the eggs then lays 2 blue eggs
        'r')
            axiom=$axiom'rrbr';; # the red egg yields a red fish who swims over the eggs then lays two red eggs, a blue egg and a red egg
    esac
    axiom=${axiom#$egg} # when the egg hatches the explosion kills its two neighbours
    echo $axiom # just to see what happens
done
