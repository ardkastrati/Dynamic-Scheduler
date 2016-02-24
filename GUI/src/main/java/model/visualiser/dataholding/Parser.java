package model.visualiser.dataholding;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Parser {
	
	private HashMap<Integer,Task> taskMap;
	
	//####DATA_START####
	// line: (ID);Time;Event;Mode;Parent;Start_Time;End_Time;Rank;Param_Size;#
	// statistic:
	// line: ID;Runtime:Parameters[];#
	
	HashMap<Integer,Task> parseToTaskList() {
		
		
		return null;
		
	}
	
	void parseBookkeeping() {
		
	}
	
	void parseStatistic(String path) {
		File file = new File(path);
		Scanner input = null;
		try {
			input = new Scanner(file);
		} catch (FileNotFoundException e) {
			// TODO Automatisch generierter Erfassungsblock
			e.printStackTrace();
		}
		String line = null;
		String[] splitLine;
		while(input.hasNextLine())  {
			while(line != "####DATA_START####") {
				line = input.nextLine();
			}
			line = input.nextLine();
			splitLine = line.split(";");
			int id = Integer.parseInt(splitLine[0]);
			int time = Integer.parseInt(splitLine[1]);
			String event = splitLine[2];
			int rank = Integer.parseInt(splitLine[7]);
			Task task;
			if(taskMap.containsKey(id)) {
				task = taskMap.get(id);
			} else {
				task = new Task();
			}
			task.setId(id);
			switch (event) {
			case "appered":
				task.setAppered(time);
				break;
			case "started":
				task.setStarted(time);
				break;
			case "ended":
				task.setEnded(time);
				break;
			}
			task.setRank(rank);
		}
		
		input.close();
	}
}
