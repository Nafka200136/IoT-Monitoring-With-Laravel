<template x-for="(status, pin) in { D5: false, D6: false, D7: false }" :key="pin">
    <div class="p-4 bg-white rounded-lg shadow-md" x-data="{ ledStatus: status }">
        <div @click="ledStatus = !ledStatus; controlLED(pin, ledStatus ? 1 : 0)"
             class="relative flex items-center w-40 h-20 p-2 bg-gray-300 rounded-full cursor-pointer"
             :class="ledStatus ? 'bg-green-600' : 'bg-gray-300'">
            <div class="flex items-center justify-center w-16 h-16 transition-transform duration-300 transform bg-white rounded-full shadow-md"
                 :class="ledStatus ? 'translate-x-20' : ''">
                <span class="font-bold text-black" x-text="pin"></span>
            </div>
            <span class="absolute font-bold text-white"
                  :class="ledStatus ? 'left-8' : 'right-8'">
                <span x-text="ledStatus ? 'ON' : 'OFF'"></span>
            </span>
        </div>
    </div>
</template>


