for i in `seq 1  20`;
do
    CMDA=$(./submarine < /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise3/lab03/submarine/input$i.txt)
    CMDB=$(cat /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise3/lab03/submarine/output$i.txt)
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
