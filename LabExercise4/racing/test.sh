for i in `seq 1  20`;
do
    CMDA=$(./racing < /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise4/lab04/racing/input$i.txt)
    CMDB=$(cat /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise4/lab04/racing/output$i.txt)
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
