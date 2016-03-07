package model.visualiser.dataholding;

import controller.ParserException;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class Parser {
	
    private HashMap<Integer,Task> taskMap;
	
	//####DATA_START####
	// line: (ID);Time;Event;Mode;Parent;Start_Time;End_Time;Rank;Param_Size;#
	// statistic:
	// line: ID;Runtime:Parameters[];#
	
    HashMap<Integer,Task> parseToTaskMap() {
        return null;	
    }
    
    
	
    public List<Event> parseStatistic(String path) throws FileNotFoundException, ParserException{
        File file = new File(path);
        Scanner input = null;
        try {
            input = new Scanner(file);
        } catch (FileNotFoundException e) {
                //TODO handle Error
        }
        String line = null;
        String[] splitLine;
            
        long runtime = -1;
        while(input.hasNextLine()) {
            while(!"####DATA_START####".equals(line)) {
                line = input.nextLine();
            }
            line = input.nextLine();
            splitLine = line.split(";");
            runtime = Long.parseLong(splitLine[0]);
            double parameters[] = new double[splitLine.length - 1];
            for(int i = 1; i < splitLine.length; i++) {
                parameters[i-1] = Double.parseDouble(splitLine[1]);
            }
              
        }
        input.close();
        return null;
    }
	
    public HashMap<Integer,Task> parseBookkeeping(String path) throws FileNotFoundException, ParserException{
	if(taskMap == null) {
            taskMap = new HashMap<Integer, Task>();
        }
                
        File file = new File(path);
	Scanner input = new Scanner(file);
	String line = input.nextLine();
	String[] splitLine;
        System.out.println("Debug");
        while(!line.contains("####DATA_START####") && input.hasNextLine()) {
            System.out.println(line);
            if (!input.hasNextLine()) {
                throw new ParserException();
            }
            line = input.nextLine();
        }     
	while(input.hasNextLine())  {
            //System.out.println("Debug in line");
            //System.out.println("Line:" + line);
            line = input.nextLine();
            splitLine = line.split(";");
            int id = Integer.parseInt(splitLine[0]);
            if(id == 0){
                continue;
            }
            Task oldTask;
            Task task = new Task();
            task = taskMap.getOrDefault(id, task);        
            long time = Long.parseLong(splitLine[1]);
            String event = splitLine[2];
            int rank = Integer.parseInt(splitLine[7]);
            task.setId(id);
            switch (event) {
            case "Appered":
                task.setAppered(time);
                break;
            case "Started":
                task.setStarted(time);
                break;
            case "Ended":
                task.setEnded(time);
                break;
            }
            task.setRank(rank);
            if(taskMap.containsKey(id)) {
                taskMap.replace(id, task);
            } else {
                taskMap.put(id, task);
            }
        }
        input.close();
        System.out.println(taskMap);
        return taskMap;
    }
}
