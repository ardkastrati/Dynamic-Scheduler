package model.visualiser.dataholding;

public class Event {
	
	private Long time;
	
	private Double[] parameters;

	public Long getTime() {
		return time;
	}

	public void setTime(Long time) {
		this.time = time;
	}

        public Double[] getParameters() {
            return parameters;
        }
        
        public void setParameters(Double[] parameters) {
            this.parameters = parameters;
        }
}