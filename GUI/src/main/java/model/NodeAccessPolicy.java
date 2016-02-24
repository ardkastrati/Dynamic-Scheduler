/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model;

/**
 *
 * @author ardkastrati
 */
public enum NodeAccessPolicy {
    /**
     * 
     */
    SHARED("shared"),
    SINGLEUSER("singleuser"),
    SINGLEJOB("singlejob"),
    SINGLETASK("singletask");
    
    private final String nodeAccessPolicy;
    
    private NodeAccessPolicy(String nodeAccessPolicy) {
        this.nodeAccessPolicy = nodeAccessPolicy;
    }
    
    @Override
    public String toString() {
        return this.nodeAccessPolicy;
    }
    
    public static NodeAccessPolicy getNodeAccessPolicyFromName(String name) {
        return valueOf(name);
    }
    
}
