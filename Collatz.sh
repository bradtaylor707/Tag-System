# there are three colors off eggs in a row: red, green and blue. Only the leftest one receives enough light to hatch
# the axiom is a string composed of 'b' letters becouase at the beginnig there are only blue eggs
# Collatz conjecture states that whatever the initial number of blue eggs, the population will extinct
# it is as of 2015 an unsolved problem
axiom='bbb'
while [ ${#axiom} -gt 1 ] # if Collatz conjecture is false this program may never halt...
do
    eggs=${axiom:0:2} # this is a 2-tag system: One looks at the 2 first eggs (actually the first one, which will kill the second one when hatching)
    case ${eggs:0:1} in # looking at the first egg's color
    # these are the transformation rules: just appending some strings
        'b')
            axiom=$axiom'gr';; # a blue fish lays a green egg then a red egg
        'g')
            axiom=$axiom'b';; # a green fish lays only a blue egg
        'r')
            axiom=$axiom'bbb';; # the red fish is the most fertile as it lays three blue eggs
    esac
    axiom=${axiom#$eggs} # removing the eggs at the left
    echo $axiom # looking at the population
done
