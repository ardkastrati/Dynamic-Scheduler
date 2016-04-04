
package model.commands.MPI;


import java.util.ArrayList;
import model.commands.ICommand;

/**
 *  This class represents the mmpirun command with all its needed parameters in dynamic scheduler.
 * @author ardkastrati
 */
public class MpiRun implements ICommand {

  /**
    * This enum represents the two possible scheduling designs of the dynamic scheduler.<br/>
    * The following list specifies the allowed designs:
    * <p>
    *  <ul>
    *   <li>MASTER_WORKER</li>
    *   <li>MULTI_QUEUE</li>
    *  </ul>
    * </p>
    * @author ardkastrati
    * @version 1.0
    *
    */
    public enum SchedulingDesign {
        /**
         * Each process can request master to access the queue.
         */
        MASTER_WORKER("master-worker"),
        /**
         * Each process has its own queue.
         */ 
        MULTI_QUEUE("multi-queue");
        
        private final String name;
        private SchedulingDesign(String name) {
            this.name = name;
        }
        
        
        /**
         * This method returns the scheduling design enum object from the name.
         * @param name the name of the design
         * @return Scheduling design enum object
         */ 
        public static SchedulingDesign getDesignFromName(String name) {
            SchedulingDesign design = null;
            switch(name) {
                case "Master/Worker Design" :
                    design = SchedulingDesign.MASTER_WORKER;
                    break;
                case "Multi-Queue Design" :
                    design = SchedulingDesign.MULTI_QUEUE;
                    break;
                default :
                    assert false;
                    break;
            }
            return design;
        }
        @Override
        public String toString() {
           return this.name;
        }
        
    }
    
    
    /**
      * This enum represents the possible scheduling strategies of the dynamic scheduler.<br/>
      * The following list specifies the allowed strategies:
      * <p>
      *  <ul>
      *   <li>FIFO</li>
      *   <li>LIFO</li>
      *   <li>SJF</li>
      *   <li>LJF</li>
      *  </ul>
      * </p>
      * @author ardkastrati
      * @version 1.0
      *
      */
    public enum SchedulingStrategy {
        /**
         * First in, first out
         */ 
        FIFO("fifo"),
        /**
         * Last in, first out
         */  
        LIFO("lifo"),
        /**
         * Shortest job first
         */ 
        SJF("sjf"),
        /**
         *  Longest job first
         */
        LJF("ljf");
        
        private final String name;
        private SchedulingStrategy(String name) {
            this.name = name;
        }
        /**
         * This method returns the scheduling strategy enum object from the name.
         * @param name the name of the strategy
         * @return Scheduling strategy enum object
         */ 
        public static SchedulingStrategy getStrategyFromName(String name) {
            SchedulingStrategy strategy = null;
            switch(name.toUpperCase()) {
                case "FIFO" :
                    strategy = SchedulingStrategy.FIFO;
                    break;
                case "LIFO" :
                    strategy = SchedulingStrategy.LIFO;
                    break;
                case "SJF" :
                    strategy = SchedulingStrategy.SJF;
                    break;
                case "LJF" :
                    strategy = SchedulingStrategy.SJF;
                    break;
                default :
                    assert false;
                    break;
            }
            return strategy;
        }
        @Override
        public String toString() {
           return this.name;
        }
    }
    
    private String parameter;
    private SchedulingDesign design;
    private SchedulingStrategy strategy;
    
    /**
     * Sets the mpirun parameters.
     * @param parameter
     */ 
    public void setParameter(String parameter) {
        this.parameter = parameter;
    }
    /**
     * Sets the design of the scheduler.
     * @param design the design
     */
    public void setDesign(SchedulingDesign design) {
        this.design = design;
    }
    /**
     * Sets the strategy of the scheduluer.
     * @param strategy the strategy
     */ 
    public void setStrategy(SchedulingStrategy strategy) {
        this.strategy = strategy;
    }
           
    @Override
    public String getCommand() {
        StringBuilder command = new StringBuilder();
        if(parameter == null && design == null && strategy == null) { return ""; }
        
       // command.append("mpirun ");
        if(parameter != null) {
            
            command.append(parameter);
        }
        System.out.println(design);
        System.out.println(strategy);
        if(design != null) {
            command.append(" --design ");
            command.append(design.toString());
            
        }
        if(strategy != null) {
           command.append(" --strategy ");
           command.append(strategy.toString());
        }
        return command.toString();
    }

    @Override
    public ArrayList<String> getScriptCommands() {
        ArrayList<String> scriptCommands = new ArrayList<>();
        scriptCommands.add(getCommand());
        return scriptCommands;
    }

    @Override
    public String toString() {
       return "mpirun";
    }
    
    /**
     * Compares to type of commands lexiographically where case is ignored.
     * @param command
     * @return
     */
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }
    
}
