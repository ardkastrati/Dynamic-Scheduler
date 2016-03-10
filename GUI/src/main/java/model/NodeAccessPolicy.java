/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model;

    /**
    * This enum represents the possible access policies of the nodes in MOAB Workload Manager.<br/>
    * The following list specifies the allowed node access policies:
    * <p>
    *  <ul>
    *   <li>SHARED</li>
    *   <li>SINGLEUSER</li>
    *   <li>SINGLEJOB</li>
    *   <li>SINGLETASK</li>
    *  </ul>
    * </p>
    * @author ardkastrati
    * @version 1.0
    *
    */
public enum NodeAccessPolicy {
    /**
     * Tasks from any combination of jobs may use available resources.
     */
    SHARED("shared"),
    /**
     * Tasks from a single job may use available resources.
     */ 
    SINGLEUSER("singleuser"),
    /**
     * A single task from a single job may run on the node. 
     */
    SINGLEJOB("singlejob"),
    /**
     * Tasks from any jobs owned by the same user may use available resources.
     */ 
    SINGLETASK("singletask");
    
    private final String nodeAccessPolicy;
    
    private NodeAccessPolicy(String nodeAccessPolicy) {
        this.nodeAccessPolicy = nodeAccessPolicy;
    }
    
    @Override
    public String toString() {
        return this.nodeAccessPolicy;
    }
    
    /**
     * This method returns the node access policy enum object from the name.
     */ 
    public static NodeAccessPolicy getNodeAccessPolicyFromName(String name) {
        return valueOf(name);
    }
    
}
