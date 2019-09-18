// HACK: this helps confused libc++ functions call the right instruction. for
// info see https://github.com/purduesigbots/pros/issues/153#issuecomment-519335375
//
// At some point this should land in pros mainline
// https://github.com/purduesigbots/pros/pull/155/files#diff-d54fdce7e622990739a43c2bc05d4860R38

void __sync_synchronize(void) {
    __sync_synchronize();
}
