package parser;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

import model.data.Task;

public class Parser {
	//####DATA_START####
	// line: (ID);Time;Event;Mode;Parent;Start_Time;End_Time;Rank;Param_Size;#
	// statistic:
	// line: ID;Runtime:Parameters[];#
	private String statistics;
	private String bookkeeping;
	private HashMap<Integer,Task> tasks;
	
	void setStatistics(String statistics) {
		this.statistics = statistics;
	}
	
	void setBookkeeping(String bookkeeping) {
		this.bookkeeping = bookkeeping;
	}
	
	

	void parse() {
		tasks = new HashMap<Integer, Task>();
		BufferedReader sr = null;
		BufferedReader br = null;
		try {
			sr = new BufferedReader(new FileReader(this.statistics));
			br = new BufferedReader(new FileReader(this.bookkeeping));
			String line;
			String lineContainer[];
			while ((line = sr.readLine()) != null) {
				do {
					line = sr.readLine();
				} while(line != "####DATA_START####");
				lineContainer = line.split(";");
				if (!tasks.containsKey(lineContainer[0])) {
					int ID = Integer.parseInt(lineContainer[0]);
					int runtime = Integer.parseInt(lineContainer[1]);
					float parameters[] = new float[lineContainer.length - 3];
					for (int i = 0; i < lineContainer.length - 3; i++) {
						parameters[i] = Float.parseFloat(lineContainer[i + 2]);
					}
					Task task = new Task(ID, runtime, parameters);
					tasks.put(ID, task);
				}
			}
			while ((line = br.readLine()) != null) {
				do {
					line = sr.readLine();
				} while(line != "####DATA_START####");
				lineContainer = line.split(";");
				if (tasks.containsKey(lineContainer[0])) {
					Task task = tasks.get(lineContainer[0]);
					if (lineContainer[2] == "Appeared") {
						task.setAppeared(Integer.parseInt(lineContainer[1]));
					} else if(lineContainer[2] == "Started") {
						task.setStart(Integer.parseInt(lineContainer[1]));
					} else if(lineContainer[2] == "Ended") {
						task.setEnd(Integer.parseInt(lineContainer[1]));
					}
				}
			}
		} catch(IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (br != null) {
					br.close();
				}
				if (sr != null) {
					sr.close();
				}
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
	}
	
}
