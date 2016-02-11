/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model;

/**
 * The memory units that are currently allowed in MOAB Workload manager.
 *
 * @author ardkastrati
 */
public enum MemoryUnit {
    
    /**
     *  Memory unit kilobyte
     */ 
    KILOBYTE("kb"),
    /**
     *  Memory unit megabyte
     */ 
    MEGABYTE("mb"),
    /**
     *  Memory unit gigabyte
     */ 
    GIGABYTE("gb");
    
    private final String memoryUnit;
    
    private MemoryUnit(String memoryUnit) {
        this.memoryUnit = memoryUnit;
    }
    
    /**
     * Returns a string representation of the memory unit.
     * @return a string representation of the memory unit.
     */
    public String toString() {
        return this.memoryUnit;
    }
}
