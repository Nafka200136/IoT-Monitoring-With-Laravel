<x-app-layout>
    <x-slot name="header">
        <h2 class="font-black text-center text-3xl text-gray-800 dark:text-gray-200 leading-tight">
            {{ __('IoT Monitoring System') }}
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-full mx-auto sm:px-6 lg:px-8">
            <div class="bg-white dark:bg-gray-800 overflow-hidden shadow-sm sm:rounded-lg">
                <div class="p-6 text-gray-900 dark:text-gray-100">

                    <div id="data" class="grid grid-cols-2 gap-4">
                        <div class="flex flex-col justify-center bg-orange-400 dark:bg-orange-950 rounded-lg shadow-md mb-6">
                            <div class="p-4">
                                <p class="text-xl">Suhu: <span id="suhu" class="font-extrabold">0</span> °C</p>
                                <p class="text-xl">Kelembaban: <span id="kelembaban" class="font-extrabold">0</span> %</p>
                            </div>
                        </div>

                        <div class="flex flex-rows justify-between mb-6" x-data="{ pins: [
                                                 { id:1, label: 'D5' },
                                                 { id:2, label: 'D6' },
                                                 { id:3, label: 'D7' }
                                            ] }">
                            <template x-data="{ status: false  }" x-for="pin in pins" :key="pin.id">
                                <div class="p-4 bg-orange-400 dark:bg-orange-950 rounded-lg shadow-md" x-data="{ ledStatus: status}">
                                    <div id="switch"
                                         @click="ledStatus = !ledStatus; controlLED(pin.label, ledStatus ? 1:0)"
                                         class="relative flex items-center w-40 h-20 p-2 bg-gray-300 dark:bg-gray-600 rounded-full cursor-pointer"
                                         :class="ledStatus ? 'bg-green-600 dark:bg-green-600' : 'bg-gray-300'">
                                        <div class="flex items-center justify-center w-16 h-16 transition-transform duration-300 transform bg-white rounded-full shadow-md"
                                             :class="ledStatus ? 'translate-x-20' : ''">
                                            <span class="font-bold text-black" x-text="pin.label"></span>
                                        </div>
                                        <span class="absolute font-bold text-white"
                                              :class="ledStatus ? 'left-8' : 'right-8'">
                                            <span x-text=" ledStatus ? 'ON' : 'OFF' "></span>
                                        </span>
                                    </div>
                                </div>
                            </template>
                        </div>
                    </div>

                    <div class="grid grid-cols-1 md:grid-cols-2 gap-4">
                        <div class="w-full bg-yellow-50 dark:bg-gray-700 mx-auto p-6 rounded-lg shadow-md">
                            <h3 class="uppercase text- text-3xl text-center font-extrabold my-6">Grafik Realtime Suhu</h3>
                            <canvas id="chartSuhu"></canvas>
                        </div>

                        <div class="w-full bg-yellow-50 dark:bg-gray-700 mx-auto p-6 rounded-lg shadow-md">
                            <h3 class="uppercase text-3xl text-center font-extrabold my-6">Grafik Realtime Kelembaban</h3>
                            <canvas id="chartKelembaban"></canvas>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</x-app-layout>
