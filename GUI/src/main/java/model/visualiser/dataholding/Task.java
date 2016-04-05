package model.visualiser.dataholding;

/**
 *
 * This class represents a Task
 */
public class Task {
	
	private long appaered;
	
	private long started;
	
	private long ended;
	
	private int rank;
	
	private long id;
        
        private long parent;

    /**
     * Returns the id of the parent task
     * @return The id of the parent task
     */
    public long getParent() {
        return parent;
    }

    /**
     * Sets the id of the parent task
     * @param parent id of the parent task
     */
    public void setParent(long parent) {
        this.parent = parent;
    }

    /**
     * Returns the time this task appeared
     * @return the time this task appeared
     */
    public long getAppaered() {
		return appaered;
	}

    /**
     * Sets the time this task appeared
     * @param appered the time this task appeared
     */
    public void setAppaered(long appaered) {
		this.appaered = appaered;
	}

    /**
     * Returns the time this task started
     * @return the time this task started
     */
    public long getStarted() {
		return started;
	}

    /**
     * Sets the time this task started
     * @param started the time this task started
     */
    public void setStarted(long started) {
		this.started = started;
	}

    /**
     * Returns the time this task ended
     * @return the time this task ended
     */
    public long getEnded() {
		return ended;
	}

    /**
     * Sets the time this task ended
     * @param ended the time this task ended
     */
    public void setEnded(long ended) {
		this.ended = ended;
	}

    /**
     * Returns the rank of the processor this task was executed on
     * @return the rank of the processor this task was executed on
     */
    public long getRank() {
		return rank;
	}

    /**
     * Sets the rank of the processor this task was executed on
     * @param rank the rank of the processor this task was executed on
     */
    public void setRank(int rank) {
		this.rank = rank;
	}

    /**
     * Returns the id of this task
     * @return the id of this task
     */
    public long getId() {
		return id;
	}

    /**
     * Sets the id of this task
     * @param id the id of this task
     */
    public void setId(long id) {
		this.id = id;
	}

    void setAppered(long time) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
