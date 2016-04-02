
package model.commands.MOAB;

import java.util.ArrayList;
import model.commands.CommandException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import model.MemoryUnit;
 
    /**
    * This enum represents the possible queue classes that can be used in MOAB Workload Manager.<br/>
    * The following list specifies the allowed classes:
    * <p>
    *  <ul>
    *   <li>DEVELOP</li>
    *   <li>SINGLENODE</li>
    *   <li>MULTINODE</li>
    *   <li>VERYLONG</li>
    *   <li>FAT</li>
    *  </ul>
    * </p>
    * @author ardkastrati
    * @version 1.0
    *
    */
public enum QueueType {
    
    /**
     * 
     */
    DEVELOP("develop"),
    
    /**
     * 
     */
    SINGLENODE("singlenode"),
    
    /**
     * 
     */
    MULTINODE("multinode"),
    
    /**
     * 
     */
    VERYLONG("verylong") ,

    /**
     *
     */
    FAT("fat");
    
    private final String type;
    
    private QueueType(String type) {
        this.type = type;
    }
    
    @Override
    public String toString() {
        return this.type;
    }
    
    /**
     * Returns the default resources that a specific queue class has.
     */ 
    public List<MoabResources> getDefaultResources() {
        List<MoabResources> defaultResources = new ArrayList<MoabResources>();
        try {
           MoabResources defaultResource1 = null;
           MoabResources defaultResource2 = null;
           MoabResources defaultResource3 = null;
            switch (this) {
                case DEVELOP:
                    defaultResource1 = MoabResources.WALLTIME;
                    defaultResource1.setParameter(600);
                    defaultResource2 = MoabResources.NODES_AND_PROCESSES_PER_NODE;
                    defaultResource2.setParameter(1,1);
                    defaultResource3 = MoabResources.PROCESSOR_MEMORY;
                    defaultResource3.setParameter(4000, MemoryUnit.MEGABYTE);
                    
                    break;
                
                case SINGLENODE:
                    defaultResource1 = MoabResources.WALLTIME;
                    defaultResource1.setParameter(1801);
                    defaultResource2 = MoabResources.NODES_AND_PROCESSES_PER_NODE;
                    defaultResource2.setParameter(1, 1);
                    defaultResource3 = MoabResources.PROCESSOR_MEMORY;
                    defaultResource3.setParameter(4000, MemoryUnit.MEGABYTE);
                    break;
                
                case MULTINODE:
                    defaultResource1 = MoabResources.WALLTIME;
                    defaultResource1.setParameter(600);
                    defaultResource2 = MoabResources.NODES_AND_PROCESSES_PER_NODE;
                    defaultResource2.setParameter(1, 1);
                    defaultResource3 = MoabResources.PROCESSOR_MEMORY;
                    defaultResource3.setParameter(4000, MemoryUnit.MEGABYTE);
                    break;
                
                case VERYLONG:
                    defaultResource1 = MoabResources.WALLTIME;
                    defaultResource1.setParameter(10801);
                    defaultResource2 = MoabResources.NODES_AND_PROCESSES_PER_NODE;
                    defaultResource2.setParameter(1, 1);
                    defaultResource3 = MoabResources.PROCESSOR_MEMORY;
                    defaultResource3.setParameter(4000, MemoryUnit.MEGABYTE);
                    
                    break;
                case FAT:
                    
                    defaultResource1 = MoabResources.WALLTIME;
                    defaultResource1.setParameter(600);
                    defaultResource2 = MoabResources.NODES_AND_PROCESSES_PER_NODE;
                    defaultResource2.setParameter(1, 1);
                    defaultResource3 = MoabResources.PROCESSOR_MEMORY;
                    defaultResource3.setParameter(32000, MemoryUnit.MEGABYTE);
                    break;
                default:
                    // This way the code is protected against later changes, e.g.
                    // introduction of new types in this enumeration type.
                    assert false : this;
                    break;
            }
           
            defaultResources.add(defaultResource1);
            defaultResources.add(defaultResource2);
            defaultResources.add(defaultResource3);
            return defaultResources;
            
        } catch (CommandException ex) {
            Logger.getLogger(QueueType.class.getName()).log(Level.SEVERE, null, ex);
        }
            return defaultResources;
    }
    
}
