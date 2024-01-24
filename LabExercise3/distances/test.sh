for i in `seq 1  20`;
do
    CMDA=$(./distances < /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise3/lab03/distances/input$i.txt)
    CMDB=$(cat /home/piyi/Documents/NTUA/ALGORITHMS/LabExercise3/lab03/distances/output$i.txt)
    if [ "$CMDA" = "$CMDB" ]; then
          echo "$i: PASSED";
    else
          echo "$i: NOT PASSED";

          echo "Your output:"
 		  echo "$CMDA"
 		  echo "Correct output:"
  		  echo "$CMDB"

fi
done
