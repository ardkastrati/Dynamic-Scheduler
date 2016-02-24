/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MOAB;

import java.util.ArrayList;
import model.commands.CommandException;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import model.MemoryUnit;

/**
 *
 * @author ardkastrati
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
    MULTINODE("multinode") {
        
    },
    
    /**
     * 
     */
    
    VERYLONG("verylong") {
        
    },

    /**
     *
     */
    FAT("fat") {
        
    };
    
    private final String type;
    
    private QueueType(String type) {
        this.type = type;
    }
    
    @Override
    public String toString() {
        return this.type;
    }
    
    
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
