using System.Runtime.InteropServices;

namespace TrabalhoDuro
{
    internal class Program
    {
        // Importações da biblioteca user32.dll para simular eventos de entrada
        [DllImport("user32.dll")]
        static extern void mouse_event(uint dwFlags, int dx, int dy, uint dwData, int dwExtraInfo);

        [DllImport("user32.dll")]
        static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, int dwExtraInfo);

        // Constantes para simulação de eventos de mouse e teclado
        const uint MOUSEEVENTF_MOVE = 0x0001;
        const uint KEYEVENTF_KEYDOWN = 0x0000;
        const uint KEYEVENTF_KEYUP = 0x0002;
        const byte VK_NUMLOCK = 0x90;
        static void Main(string[] args)
        {
            
            int timeKelle = 0;
            while (true)
            {
                Console.Clear();
                Console.WriteLine("Trabalho duro iniciado. Aperte Ctrl+C para parar");
                Console.WriteLine($"Tempo matado: {timeKelle} minutos.");
                Console.WriteLine("Simulando movimento do mouse...");
                mouse_event(MOUSEEVENTF_MOVE, 1, 0, 0, 0);
                mouse_event(MOUSEEVENTF_MOVE, -1, 0, 0, 0);


                Console.WriteLine("Mudando o estado do num lock");
                keybd_event(VK_NUMLOCK, 0x45, KEYEVENTF_KEYDOWN, 0);
                keybd_event(VK_NUMLOCK, 0x45, KEYEVENTF_KEYUP, 0);

                
                Console.WriteLine("Esperando 1 minuto");
                Thread.Sleep(TimeSpan.FromMinutes(1));
                timeKelle++;
            }
        }
    }
}
