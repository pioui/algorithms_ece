for i in `seq 1  20`;
do
    CMDA=$(./roadtrip < /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise1/lab01/roadtrip/input$i.txt)
    CMDB=$(cat /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise1/lab01/roadtrip/output$i.txt)
    if [ "$CMDA" = "$CMDB" ]; then
          echo "$i: PASSED";
    else
          echo "$i: FAILED";

          echo "Your Output:"
 		  echo "$CMDA"
 		  echo "Correct Output:"
 		  echo "$CMDB"
fi
done
