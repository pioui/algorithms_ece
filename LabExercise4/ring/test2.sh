i=7
CMDA=$(./ring < /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise4/lab04/ring/input$i.txt)
CMDB=$(cat /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise4/lab04/ring/output$i.txt)
if [ "$CMDA" = "$CMDB" ]; 
then
    echo "$i: PASSED";
else
    echo "$i: FAILED";
    echo "Your Output:"
	echo "$CMDA"
 	echo "Correct Output:"
 	echo "$CMDB"
fi



# Compile: chmod +x test.sh
# Run: ./test.sh