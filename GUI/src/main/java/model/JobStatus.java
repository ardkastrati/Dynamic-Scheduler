/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model;

/**
 *
 * @author ardkastrati
 */
public enum JobStatus {
    ACTIVE("active"),
    ELIGIBLE("eligible"),
    BLOCKED("blocked");
    
    private final String status;
    
    private JobStatus(String status) {
        this.status = status;
    }
}
