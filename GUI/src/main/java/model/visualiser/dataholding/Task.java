package model.visualiser.dataholding;

public class Task {
	
	private long appered;
	
	private long started;
	
	private long ended;
	
	private int rank;
	
	private int id;

	public long getAppered() {
		return appered;
	}

	public void setAppered(long appered) {
		this.appered = appered;
	}

	public long getStarted() {
		return started;
	}

	public void setStarted(long started) {
		this.started = started;
	}

	public long getEnded() {
		return ended;
	}

	public void setEnded(long ended) {
		this.ended = ended;
	}

	public long getRank() {
		return rank;
	}

	public void setRank(int rank) {
		this.rank = rank;
	}

	public long getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
}
