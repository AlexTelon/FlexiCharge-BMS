# How to charge lithium-ion batteries
___

## Introduction

A battery can either charge, discharge or be in a idle state.
During the discharge state of the li-ion battery,
the recommended cut-off voltage for most 3.7V lithium-ion battery is at 3.0V 
according to the FlexiCharge hardware architect (Davidsson, R). 
This means the battery has reached its lowest
point of energy stored and needs to be charged. 

During the state of charging of
the li-ion battery, the end-of charge voltage is at 4.2V. This is the top recommended 
voltage peak for the li-ion battery. 
However, according to a videoblog (EEVBlog) on youtube, to set the end-of charge peak at
4.1V instead would increase the battery cycle life at the expence of less charging capacity. 
This also creates higher security, all because the 4.2V is a critical voltage level
with few margins not to overcharge the battery cell. 
Some batteries about 4.2V +1% down to +0.3% accuracy when charging.  

___

## Modes of charging

* **Constant current/Constant voltage**
* **Target voltage method**
* **Constant current method**

### Constant current/Constant voltage (CC/CV)
According to the book (A Systems Approach To Lithium-Ion Battery Management) the 
CC/CV method is discussed as the most prefered method
for charging lithium-ion batteries. In this method, the batteries should be charged 
at constant current level while voltage slowly increases to desired level (end-of charge).
After this voltage level is reached, the charging switches to constant voltage. 
Gradually the current level decreases to a predefined level. The total time it takes
for the battery to charge depends on the C-time. For example 1C = 1 hour of charge
and 2C = 30 min.  

### *_The other modes not relevant_

There is three different charging steps that would be performed to charge 
the lithium-ion battery in CC/CV. The first step is optional but the order is as 
follows: 

**1. Precharge state** 

**2. Constant current state**

**3. Constant voltage state**

___

### Precharge state

The youtube videoblogg (EEVBlog) states that when a single lithium-ion battery
is around 20% of its full current capacity or when its voltage is under 2.8 V, 
the battery needs precharging.
This is to prevent damage before entering the next state (CC). The charging 
current is set at 20% of full capacity and voltage slowly increases to 2.8 V. 
Then after this we can enter the next state (CC). This precharge state is however optional. 


### Constant current state

The battery gets charged with a constant current at the same level as the battery's 
full capacity in amps. The voltage starts at the same voltage level as the current
voltage state of the battery and slowly increases to the end-of charge level at 
4.2V or 4.1V. After this voltage is reached, the li-ion battery is now loaded at 
about 80% of its full current capacity. 


### Constant voltage state

When the CC-state is finished, the current decreases and the voltage holds the 
same end-of charge voltage until the current level is about 10% of its full capacity.
Then the charging should stop and the charging is done. 










