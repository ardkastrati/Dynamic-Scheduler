package model.data;

public class Task {
	private int ID;
	private int runtime;
	private float parameters[];
	private int appeared;
	private int start;
	private int end;
	private int processedOn;
	
	public Task(int ID, int runtime, float parameters[]) {
		this.ID = ID;
		this.runtime = runtime;
		this.parameters = parameters;
	}
	
	int getID() {
		return this.ID;
	}
	
	int getRuntime() {
		return this.runtime;
	}
	
	float[] getParameters() {
		return this.parameters;
	}

	/**
	 * @return appered
	 */
	public int getAppeared() {
		return appeared;
	}

	/**
	 * @param appered das zu setzende Objekt appered
	 */
	public void setAppeared(int appeared) {
		this.appeared = appeared;
	}

	/**
	 * @return start
	 */
	public int getStart() {
		return start;
	}

	/**
	 * @param start das zu setzende Objekt start
	 */
	public void setStart(int start) {
		this.start = start;
	}

	/**
	 * @return end
	 */
	public int getEnd() {
		return end;
	}

	/**
	 * @param end das zu setzende Objekt end
	 */
	public void setEnd(int end) {
		this.end = end;
	}

	/**
	 * @return processedOn
	 */
	public int getProcessedOn() {
		return processedOn;
	}

	/**
	 * @param processedOn das zu setzende Objekt processedOn
	 */
	public void setProcessedOn(int processedOn) {
		this.processedOn = processedOn;
	}
	
	
}