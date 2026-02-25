#include "agent_impl_2.h"


int main(void) {
    if (system("touch /tmp/secret_hash.txt") != 0) return -1;

    srand(42);

    /* Définition des états et des actions */

    char* state_names[] = {
        "Init", "Crack", "Sudo", "Curl"
    };

    char* action_names[] = {
        "Scan_Ports", "Exploit_Vuln", "Mouvement_Lateral", "Exfiltration"
    };

    ActionFunc actionsCalls[] = {
        scanSimu, exploitSimu, escalationSimu, exfiltrationSimu
    };

    /* Instantiation des tableaux de données  */

    int nStates = 4;
    int nActions = 4;

    RLState states[nStates];
    RLAction actions[nActions];

    for (int i = 0; i < nStates; ++i) {
        states[i].id = i;
        states[i].label = state_names[i];
        states[i].context = NULL;
    }

    for (int j = 0; j < nActions; ++j) {
        actions[j].id = j;
        actions[j].name = action_names[j];
        actions[j].execute = actionsCalls[j];
        actions[j].args = NULL;
    }

    /* Création de l'environnement et du modèle */

    RLEnv *env = RLEnvCreate(
        nStates, nActions, 
        states, actions,
        generateCyberSimpleMatrices
    );

    RLModel *m = RLModelCreate(env);

    RLConfig config = {
        .gamma = 0.9,
        .epsilon = 0.1,
        .alpha = 1,
        .steps = 10,
        .epochs = 100
    };

    RLModelSetConfig(m, config);

    /* --- Q-Learning --- */

    QLearning(m);
    RLModelPrintQTable(m);
    RLModelPrintPolicy(m);

    /* -------- Création et Exécution de l'Agent -------- */

    RLAgent agent = {
        .name = "Cyber",
        .initialState = states[0], 
        .goalState = states[nStates - 1],
        .maxIter = 20,
        .reward = 0,
        .sucess = false
    };

    printf("--- Lancement de l'Agent ---\n");

    executeAgent(m, &agent);

    if (agent.sucess) {
        printf("\nMISSION REUSSIE\n");
    } else {
        printf("ECHEC\n");
    }

    /* ----------------------- */

    RLModelDelete(&m);
    RLEnvDelete(&env);

    return 0;
}
