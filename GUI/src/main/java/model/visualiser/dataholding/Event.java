package model.visualiser.dataholding;

/**
 *
 * Represents a statistic event
 */
public class Event {
	
	private Long time;
	
	private Double[] parameters;

    /**
     * Returns the time of this event
     * @return the time of this event
     */
    public Long getTime() {
		return time;
	}

    /**
     * Sets the time of this event
     * @param time the time of this event
     */
    public void setTime(Long time) {
		this.time = time;
	}

    /**
     * Returns the parameters of this event 
     * @return the parameters of this event 
     */
    public Double[] getParameters() {
            return parameters;
        }
        
    /**
     * Sets the parameters of this event 
     * @param parameters the parameters of this event 
     */
    public void setParameters(Double[] parameters) {
            this.parameters = parameters;
        }
}