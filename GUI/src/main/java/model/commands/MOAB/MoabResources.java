package model.commands.MOAB;


import model.commands.CommandException;
import model.MemoryUnit;
import model.NodeAccessPolicy;

public enum MoabResources {
        
        
       /* NODES ("nodes"){
            private int numOfNodes;
            @Override
            public String getParameter() {
                assert numOfNodes >= 0;
                StringBuilder resourceCommand = new StringBuilder();
                resourceCommand.append("nodes=");
                resourceCommand.append(Integer.toString(numOfNodes));
                return resourceCommand.toString();
            }

            @Override
            public void setParameter(Object... parameters) throws CommandException {
                checkNumOfParameters(1, parameters);
                if (parameters[0] instanceof Integer) {
                    numOfNodes = (Integer) parameters[0];
                } else {
                     throw new CommandException("Parameter \"nodes\" needs an integer as a parameter!");
                }
            }
            
        },*/
    
        NODES_AND_PROCESSES_PER_NODE("nodes") {
            private int numOfNodes;
            private int numOfProcessesPerNode;
            
            @Override
            public String getParameter() {
               assert numOfProcessesPerNode >= 0;
                StringBuilder resourceCommand = new StringBuilder();
                resourceCommand.append("nodes=");
                resourceCommand.append(Integer.toString(numOfNodes));
                resourceCommand.append(":ppn=");
                resourceCommand.append(numOfProcessesPerNode);
                return resourceCommand.toString();   
            }

            @Override
            public void setParameter(Object... parameters) throws CommandException {
                checkNumOfParameters(2, parameters);
                
                if (parameters[0] instanceof Integer && parameters[1] instanceof Integer ) {
                     numOfNodes = (Integer) parameters[0];
                     numOfProcessesPerNode = (Integer) parameters[1];
                } else {
                     throw new CommandException("Parameter \"processes per node\" need an integer as a parameter!");
                }
            }

            
        },
        
        WALLTIME("walltime") {
            /**
             * Wall-clock time in seconds.
             */
            private int walltime;
            
            //TODO: Support for HH:MM:SS format

            @Override
            public String getParameter() {
                assert walltime >= 0;
                
                StringBuilder resourceCommand = new StringBuilder();
                resourceCommand.append("walltime=");
                resourceCommand.append(walltime);
               
                return resourceCommand.toString();  
            }

            @Override
            public void setParameter(Object... parameters) throws CommandException {
                checkNumOfParameters(1, parameters);
                
                if (parameters[0] instanceof Integer) {
                     walltime = (Integer) parameters[0];
                } else {
                     throw new CommandException("Parameter \"walltime\" needs an integer as a parameter!");
                }
            }
            
            
            
        },
        
        /**
         * Maximum amount of physical memory used by any single process of the job in MB.
         * 
         */
        PROCESSOR_MEMORY("pmem"){
            private int processMemory;
           

            @Override
            public String getParameter() {
                assert processMemory >= 0;
                StringBuilder resourceCommand = new StringBuilder();
                resourceCommand.append("pmem=");
                resourceCommand.append(processMemory);
                
                return resourceCommand.toString();
            }

            @Override
            public void setParameter(Object... parameters) throws CommandException {
                checkNumOfParameters(1, parameters);
                
                if (parameters[0] instanceof Integer && parameters[1] instanceof MemoryUnit ) {
                     processMemory = (Integer) parameters[0];
                    
                } else {
                     throw new CommandException("Parameter \"pmem\" needs an integer as a parameter!");
                }
            }
            
        },
        
        MOAB_PROCESSOR_MEMORY_UNIT("memoryUnit") {
            private MemoryUnit unit;
            @Override
            public String getParameter() {
                return unit.name();
            }

            @Override
            public void setParameter(Object... parameters) throws CommandException {
                 checkNumOfParameters(1, parameters);
                
                if (parameters[0] instanceof MemoryUnit ) {
                     unit = (MemoryUnit) parameters[0];  
                } else {
                     throw new CommandException("Parameter has no memory unit !");
                }
            }
            
        },
        
        RESERVATION_NAME("advres") {
            
            private String reservationName;
            
            @Override
            public String getParameter() {
                assert reservationName != null;
                
                StringBuilder resourceCommand = new StringBuilder();
                resourceCommand.append("advres=");
                resourceCommand.append(reservationName);
                
                return resourceCommand.toString();
            }

            @Override
            public void setParameter(Object... parameters) throws CommandException {
                checkNumOfParameters(1, parameters);
                
                if (parameters[0] instanceof String) {
                     reservationName = (String) parameters[0];
                    
                } else {
                     throw new CommandException("Parameter \"advres\" needs a String as a parameter!");
                }
            }
            
            
        },
       
        NODE_ACCESSPOLICY("naccesspolicy") {
           
            private NodeAccessPolicy nodeAccessPolicy;
            

             @Override
            public String getParameter() {
                assert nodeAccessPolicy != null;
                
                StringBuilder resourceCommand = new StringBuilder();
                resourceCommand.append("naccesspolicy=");
                resourceCommand.append(nodeAccessPolicy.toString());
                
                return resourceCommand.toString();
            }


             @Override
            public void setParameter(Object... parameters) throws CommandException {
                checkNumOfParameters(1, parameters);
                
                if (parameters[0] instanceof NodeAccessPolicy) {
                     nodeAccessPolicy = (NodeAccessPolicy) parameters[0];
                    
                } else {
                     throw new CommandException("Parameter \"node access policy\" needs a String as a parameter!");
                }
            }
            
        };
        
            
        private String commandName;
        
        private MoabResources(String commandName) {
            this.commandName = commandName;
        }
        
        /**
         * Returns a string representation of this parameter's name.
         * @return a string representation of this parameter's name
         */
        public abstract String getParameter() ;
        
        /**
         * Sets the parameter(s) of the specified command.
         * @param parameters all parameters the specific command needs
         * @see ICommand
         * @throws CommandException if the command is not written properly.
         */
        public abstract void setParameter(Object... parameters) throws CommandException;
        
        /**
         * This method helps the method {@link Command#setParameter(Object...)} to
         * check if the number of parameters is correct.
         * @param x number of needed parameters
         * @param parameters the command parameters.
         * @see Command
         * @throws CommandException if the command is not written properly
         */
        protected void checkNumOfParameters(int x, Object... parameters) throws CommandException {
            
            if (parameters == null && x != 0) {
                throw new CommandException("Expected a parameter but didn't find one.");
            }
            
            if (x != parameters.length) {
                throw new CommandException("The given parameter is invalid.");
            }
    }

        /**
         * Returns a string representation of this command's name.
         * @return a string representation of this command's name
         */
        public String toString() {
            return this.commandName;
        }
    
  

}
