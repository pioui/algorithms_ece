for i in `seq 1  20`;
do
    CMDA=$(./xmaslightings < /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise2/lab02/xmaslightings/input$i.txt)
    CMDB=$(cat /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise2/lab02/xmaslightings/output$i.txt)
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
