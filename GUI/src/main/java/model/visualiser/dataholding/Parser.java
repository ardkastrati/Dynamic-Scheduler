package model.visualiser.dataholding;

import controller.ParserException;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

/**
 * This class parses statistic and bookkeeping file
 * 
 */
public class Parser {
	
    private HashMap<Integer,Task> taskMap;
	
	//####DATA_START####
	// line: (ID);Time;Event;Mode;Parent;Start_Time;End_Time;Rank;Param_Size;#
	// statistic:
	// line: ID;Runtime:Parameters[];#
	
    HashMap<Integer,Task> parseToTaskMap() {
        return null;	
    }
    
    /**
     * Parses the statistic file. For each statistic event a Event instance is created.
     * The Events are returned in a list
     * @param path Path to the statistic file on the disk
     * @return a list of statistic events
     * @throws FileNotFoundException thrown if file was not found
     * @throws ParserException thrown if the file was not structured as expected
     */
    public List<Event> parseStatistic(String path) throws FileNotFoundException, ParserException{
        List<Event> eventList = new ArrayList<Event>();
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
        while(!"####DATA_START####".equals(line)) {
            if (!input.hasNextLine()) {
                throw new ParserException();
            }
            line = input.nextLine();
            }
        while(input.hasNextLine()) {
            line = input.nextLine();
            splitLine = line.split(";");
            runtime = Long.parseLong(splitLine[0]);
            Double parameters[] = new Double[splitLine.length - 1];
            for(int i = 1; i < splitLine.length; i++) {
                parameters[i-1] = Double.parseDouble(splitLine[1]);
            }
            Event event = new Event();
            event.setTime(runtime);
            event.setParameters(parameters);
            eventList.add(event);
        }
        input.close();
        return eventList;
    }
	
    /**
     * Parses the bookkeeping file. Each Task is stored in a instance of task.
     * The tasks will be returned in a HashMap, indexed by the id.
     * @param path Path to the bookkeeping file on the disk
     * @return HashMap of tasks
     * @throws FileNotFoundException thrown if file was not found
     * @throws ParserException thrown if the file was not structured as expected
     */
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
            int parent = Integer.parseInt(splitLine[4]);
            task.setParent(parent);
            int rank = Integer.parseInt(splitLine[7]);
            task.setId(id);
            switch (event) {
            case "Appered":
                task.setAppaered(time);
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
